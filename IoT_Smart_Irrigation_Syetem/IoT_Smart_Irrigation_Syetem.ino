#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <string.h>

const int rs = 13;
const int en = 12;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int soilPin = A0;
const int pumpRelay = 7;

SoftwareSerial espSerial(2, 3);

int soilValue = 0;
int pumpState = 0;
int manualPumpCommand = -1;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

char receivedCommand[20];
byte commandIndex = 0;

void setup()
{
  pinMode(pumpRelay, OUTPUT);
  digitalWrite(pumpRelay, LOW);

  espSerial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");

  delay(2000);
  lcd.clear();
}

void loop()
{
  readESPCommand();

  soilValue = analogRead(soilPin);

  if (manualPumpCommand == 1)
  {
    pumpState = 1;
  }
  else if (manualPumpCommand == 0)
  {
    pumpState = 0;
  }
  else
  {
    if (soilValue >= 900)
    {
      pumpState = 1;
    }
    else
    {
      pumpState = 0;
    }
  }

  if (pumpState == 1)
  {
    digitalWrite(pumpRelay, HIGH);
  }
  else
  {
    digitalWrite(pumpRelay, LOW);
  }

  displayStatus();

  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis();

    espSerial.print("SOIL:");
    espSerial.println(soilValue);
  }
}

void readESPCommand()
{
  while (espSerial.available() > 0)
  {
    char receivedChar = espSerial.read();

    if (receivedChar == '\n')
    {
      receivedCommand[commandIndex] = '\0';

      if (strcmp(receivedCommand, "PUMP_ON") == 0)
      {
        manualPumpCommand = 1;
      }
      else if (strcmp(receivedCommand, "PUMP_OFF") == 0)
      {
        manualPumpCommand = 0;
      }
      else if (strcmp(receivedCommand, "AUTO") == 0)
      {
        manualPumpCommand = -1;
      }

      commandIndex = 0;
    }
    else if (receivedChar != '\r')
    {
      if (commandIndex < sizeof(receivedCommand) - 1)
      {
        receivedCommand[commandIndex++] = receivedChar;
      }
      else
      {
        commandIndex = 0;
      }
    }
  }
}

void displayStatus()
{
  lcd.setCursor(0, 0);
  lcd.print("Soil:");
  lcd.print(soilValue);
  lcd.print("       ");

  lcd.setCursor(0, 1);

  if (manualPumpCommand == 1)
  {
    lcd.print("Manual Pump ON ");
  }
  else if (manualPumpCommand == 0)
  {
    lcd.print("Manual Pump OFF");
  }
  else if (soilValue >= 900)
  {
    lcd.print("Dry - Pump ON  ");
  }
  else if (soilValue >= 600)
  {
    lcd.print("Slight Moist   ");
  }
  else if (soilValue >= 300)
  {
    lcd.print("Wet Soil       ");
  }
  else
  {
    lcd.print("Very Wet       ");
  }
}
