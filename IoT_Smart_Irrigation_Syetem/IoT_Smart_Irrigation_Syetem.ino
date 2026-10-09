#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

const int rs = 13;
const int en = 12;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int soilPin = A0;
const int pumpRelay = 7;

SoftwareSerial esp(2, 3);

const char WIFI_SSID[] = "YOUR_WIFI_NAME";
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";

const char BLYNK_TOKEN[] = "YOUR_BLYNK_AUTH_TOKEN";

const int DRY_THRESHOLD = 900;
const int MOIST_THRESHOLD = 600;
const int WET_THRESHOLD = 300;

int soilValue = 0;
int pumpState = 0;
int automaticMode = 1;
int pumpOverride = 0;

String soilCondition = "";

unsigned long lastCloudUpdate = 0;
unsigned long lastSensorRead = 0;

const unsigned long SENSOR_INTERVAL = 500;
const unsigned long CLOUD_INTERVAL = 5000;

String responseBuffer = "";

void sendAT(const String &command, unsigned long waitTime)
{
  while (esp.available())
  {
    esp.read();
  }

  esp.println(command);

  unsigned long startTime = millis();

  while (millis() - startTime < waitTime)
  {
    while (esp.available())
    {
      char c = esp.read();
      Serial.write(c);
    }
  }
}

bool waitForResponse(const String &expected, unsigned long timeout)
{
  responseBuffer = "";

  unsigned long startTime = millis();

  while (millis() - startTime < timeout)
  {
    while (esp.available())
    {
      char c = esp.read();

      responseBuffer += c;

      if (responseBuffer.indexOf(expected) >= 0)
      {
        return true;
      }

      if (responseBuffer.length() > 250)
      {
        responseBuffer.remove(0, 100);
      }
    }
  }

  return false;
}

bool sendATCheck(const String &command,
                 const String &expected,
                 unsigned long timeout)
{
  while (esp.available())
  {
    esp.read();
  }

  esp.println(command);

  return waitForResponse(expected, timeout);
}

bool connectWiFi()
{
  if (!sendATCheck("AT", "OK", 2000))
  {
    return false;
  }

  sendAT("ATE0", 1000);

  if (!sendATCheck("AT+CWMODE=1", "OK", 2000))
  {
    return false;
  }

  String command = "AT+CWJAP=\"";
  command += WIFI_SSID;
  command += "\",\"";
  command += WIFI_PASSWORD;
  command += "\"";

  if (!sendATCheck(command, "OK", 20000))
  {
    return false;
  }

  return true;
}

void setPump(int state)
{
  pumpState = state;

  digitalWrite(pumpRelay, state ? HIGH : LOW);
}

void updatePump()
{
  if (automaticMode)
  {
    if (soilValue >= DRY_THRESHOLD)
    {
      setPump(1);
    }
    else
    {
      setPump(0);
    }
  }
  else
  {
    setPump(pumpOverride);
  }
}

void classifySoil()
{
  if (soilValue >= DRY_THRESHOLD)
  {
    soilCondition = "Dry Soil";
  }
  else if (soilValue >= MOIST_THRESHOLD)
  {
    soilCondition = "Slight Moist";
  }
  else if (soilValue >= WET_THRESHOLD)
  {
    soilCondition = "Wet Soil";
  }
  else
  {
    soilCondition = "In Water";
  }
}

void updateLCD()
{
  lcd.setCursor(0, 0);
  lcd.print("Value:");
  lcd.print(soilValue);
  lcd.print("      ");

  lcd.setCursor(0, 1);

  if (pumpState)
  {
    lcd.print("Pump ON         ");
  }
  else
  {
    lcd.print(soilCondition);
    lcd.print("    ");
  }
}

bool sendBlynkUpdate()
{
  String path = "/external/api/update?token=";
  path += BLYNK_TOKEN;
  path += "&V0=";
  path += String(soilValue);
  path += "&V1=";
  path += soilCondition;
  path += "&V2=";
  path += String(pumpState);

  String command = "AT+CIPSTART=\"TCP\",\"blynk.cloud\",80";

  if (!sendATCheck(command, "OK", 5000))
  {
    if (responseBuffer.indexOf("ALREADY CONNECTED") < 0)
    {
      return false;
    }
  }

  String request = "GET ";
  request += path;
  request += " HTTP/1.1\r\nHost: blynk.cloud\r\nConnection: close\r\n\r\n";

  command = "AT+CIPSEND=";
  command += String(request.length());

  if (!sendATCheck(command, ">", 3000))
  {
    return false;
  }

  esp.print(request);

  bool sent = waitForResponse("SEND OK", 5000);

  unsigned long startTime = millis();

  while (millis() - startTime < 3000)
  {
    while (esp.available())
    {
      Serial.write(esp.read());
    }
  }

  return sent;
}

void setup()
{
  Serial.begin(9600);
  esp.begin(9600);

  pinMode(pumpRelay, OUTPUT);
  setPump(0);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  lcd.clear();

  Serial.println("Smart Irrigation System");

  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  bool connected = connectWiFi();

  lcd.clear();

  if (connected)
  {
    lcd.print("WiFi Connected");
    Serial.println("WiFi connected");
  }
  else
  {
    lcd.print("WiFi Failed");
    Serial.println("WiFi connection failed");
  }

  delay(1500);
  lcd.clear();
}

void loop()
{
  unsigned long now = millis();

  if (now - lastSensorRead >= SENSOR_INTERVAL)
  {
    lastSensorRead = now;

    soilValue = analogRead(soilPin);

    classifySoil();
    updatePump();
    updateLCD();

    Serial.print("Soil Value: ");
    Serial.print(soilValue);

    Serial.print(" | Condition: ");
    Serial.print(soilCondition);

    Serial.print(" | Pump: ");
    Serial.println(pumpState ? "ON" : "OFF");
  }

  if (now - lastCloudUpdate >= CLOUD_INTERVAL)
  {
    lastCloudUpdate = now;

    bool result = sendBlynkUpdate();

    if (result)
    {
      Serial.println("Cloud update sent");
    }
    else
    {
      Serial.println("Cloud update failed");
    }
  }
}

