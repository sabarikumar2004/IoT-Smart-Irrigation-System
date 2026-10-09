#include <LiquidCrystal.h>

// ==================================================
// LCD Connections
// ==================================================
const int rs = 13;
const int en = 12;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ==================================================
// Soil Moisture Sensor
// ==================================================
const int soilPin = A0;
int soilValue;

// ==================================================
// Water Pump Relay
// ==================================================
const int pumpRelay = 7;

void setup()
{
  // Initialize LCD
  lcd.begin(16, 2);

  // Initialize relay
  pinMode(pumpRelay, OUTPUT);

  // Pump OFF initially
  digitalWrite(pumpRelay, LOW);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Read soil moisture sensor
  soilValue = analogRead(soilPin);

  // Display soil moisture value
  lcd.setCursor(0, 0);
  lcd.print("Value:");
  lcd.print(soilValue);
  lcd.print("    ");

  lcd.setCursor(0, 1);

  // ==================================================
  // Dry Soil - Pump ON
  // ==================================================
  if (soilValue >= 900)
  {
    lcd.print("Dry Soil      ");

    // Turn ON water pump
    digitalWrite(pumpRelay, HIGH);
  }

  // ==================================================
  // Slightly Moist - Pump OFF
  // ==================================================
  else if (soilValue >= 600)
  {
    lcd.print("Slight Moist  ");

    // Turn OFF water pump
    digitalWrite(pumpRelay, LOW);
  }

  // ==================================================
  // Wet Soil - Pump OFF
  // ==================================================
  else if (soilValue >= 300)
  {
    lcd.print("Wet Soil      ");

    // Turn OFF water pump
    digitalWrite(pumpRelay, LOW);
  }

  // ==================================================
  // Sensor in Water - Pump OFF
  // ==================================================
  else
  {
    lcd.print("In Water      ");

    // Turn OFF water pump
    digitalWrite(pumpRelay, LOW);
  }

  delay(500);
}