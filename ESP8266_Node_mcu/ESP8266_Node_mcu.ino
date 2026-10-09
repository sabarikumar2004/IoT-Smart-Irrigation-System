#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

SoftwareSerial arduinoSerial(D6, D7);

BlynkTimer timer;

int soilValue = 0;
bool manualMode = false;
bool pumpState = false;

char receivedData[30];
byte dataIndex = 0;

void sendSoilValue()
{
  Blynk.virtualWrite(V0, soilValue);
}

BLYNK_WRITE(V1)
{
  int command = param.asInt();

  manualMode = true;
  pumpState = (command == 1);

  if (pumpState)
  {
    arduinoSerial.println("PUMP_ON");
  }
  else
  {
    arduinoSerial.println("PUMP_OFF");
  }
}

BLYNK_WRITE(V2)
{
  int command = param.asInt();

  if (command == 1)
  {
    manualMode = false;
    arduinoSerial.println("AUTO");

    Blynk.virtualWrite(V1, 0);
  }
}

void readArduinoData()
{
  while (arduinoSerial.available() > 0)
  {
    char receivedChar = arduinoSerial.read();

    if (receivedChar == '\n')
    {
      receivedData[dataIndex] = '\0';

      if (strncmp(receivedData, "SOIL:", 5) == 0)
      {
        soilValue = atoi(receivedData + 5);
      }

      dataIndex = 0;
    }
    else if (receivedChar != '\r')
    {
      if (dataIndex < sizeof(receivedData) - 1)
      {
        receivedData[dataIndex++] = receivedChar;
      }
      else
      {
        dataIndex = 0;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  arduinoSerial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSoilValue);
}

void loop()
{
  Blynk.run();
  timer.run();
  readArduinoData();
}

