# 🌱 IoT-Based Smart Irrigation System

<img src="Image/project_thumbnail.png" alt="IoT-Based Smart Irrigation System" width="800">

## 📌 Project Overview

The **IoT-Based Smart Irrigation System** monitors soil moisture and controls a water pump automatically using an Arduino Uno. An ESP8266 NodeMCU provides Wi-Fi connectivity and enables remote monitoring and pump control through the Blynk IoT platform.

The Arduino Uno reads the soil moisture sensor, displays readings on a 16x2 LCD, and controls the water pump through a relay module. The NodeMCU communicates with the Arduino using UART and connects to Blynk Cloud over Wi-Fi.

Users can monitor soil moisture readings and send pump control commands through the Blynk dashboard or mobile application.

**Project status:** The source code and integration design are prepared. Complete hardware, Wi-Fi, Blynk Cloud, and mobile app operation must be tested before all features can be marked as working.

---

## ✨ Features

* Soil moisture monitoring using an analog sensor
* Automatic water pump control based on soil moisture readings
* Real-time sensor reading display on a 16x2 LCD
* Arduino Uno and ESP8266 NodeMCU integration
* UART serial communication between the two microcontrollers
* Wi-Fi connectivity using ESP8266
* Blynk Cloud integration for remote monitoring
* Manual pump ON/OFF commands through Blynk
* Automatic irrigation mode selection
* Separate code for Arduino Uno and ESP8266 NodeMCU

---

## 🛠️ Hardware Components

| S.No. | Component             | Purpose                             |
| ----- | --------------------- | ----------------------------------- |
| 1     | Arduino Uno           | Sensor reading and pump control     |
| 2     | ESP8266 NodeMCU       | Wi-Fi and Blynk Cloud connectivity  |
| 3     | Soil moisture sensor  | Measures soil moisture level        |
| 4     | 16x2 LCD              | Displays sensor readings and status |
| 5     | Relay module          | Controls the pump switching circuit |
| 6     | Water pump            | Supplies water to the plants        |
| 7     | Jumper wires          | Hardware connections                |
| 8     | USB cables            | Programming and powering the boards |
| 9     | Suitable power supply | Supplies power to the system        |

---

## 💻 Software and Tools

* Arduino IDE
* Arduino AVR Boards package
* ESP8266 board package
* LiquidCrystal library
* SoftwareSerial library
* Blynk library
* ESP8266WiFi library
* Blynk IoT Cloud
* Blynk mobile application

---

## 🏗️ System Architecture

The project uses two microcontrollers, each with a separate responsibility.

### 1. Arduino Uno

The Arduino Uno performs the main irrigation control functions:

* Reads the analog soil moisture sensor through pin A0.
* Displays the soil reading and status on the LCD.
* Controls the relay connected to digital pin D7.
* Automatically controls the pump using a soil reading threshold.
* Sends soil readings to the NodeMCU through UART.
* Receives manual pump commands and automatic mode commands from the NodeMCU.

### 2. ESP8266 NodeMCU

The ESP8266 NodeMCU provides IoT connectivity:

* Connects to a Wi-Fi network.
* Connects to Blynk Cloud.
* Receives soil readings from the Arduino Uno.
* Sends sensor readings to the Blynk dashboard.
* Receives remote pump control commands from Blynk.
* Forwards pump commands to the Arduino Uno through UART.

### 3. Blynk Cloud and Mobile Application

Blynk provides the remote monitoring and control interface.

* Displays soil moisture readings.
* Provides a manual pump ON/OFF control.
* Provides a command to return the system to automatic mode.

These functions require successful configuration and testing of the NodeMCU, Wi-Fi connection, Blynk Cloud, and mobile application.

---

## 📂 Project Folder Structure

```text
IoT-Smart-Irrigation-System/
│
├── Arduino_Uno/
│   └── Smart_Irrigation_Arduino.ino
│
├── ESP8266_Node_mcu/
│   └── ESP8266_Node_mcu.ino
│
├── Image/
│   └── project_thumbnail.png
│
└── README.md
```

---

## 🔌 Hardware Connections

### 1. Soil Moisture Sensor to Arduino Uno

| Soil Sensor Pin    | Arduino Uno                                   |
| ------------------ | --------------------------------------------- |
| Analog Output (AO) | A0                                            |
| VCC                | According to the sensor module specifications |
| GND                | GND                                           |

The Arduino reads the analog output using `analogRead(A0)`. The ADC reading ranges from 0 to 1023.

### 2. 16x2 LCD to Arduino Uno

The LCD uses the following pin configuration in the Arduino code.

| LCD Signal | Arduino Uno Pin |
| ---------- | --------------- |
| RS         | D13             |
| EN         | D12             |
| D4         | D8              |
| D5         | D9              |
| D6         | D10             |
| D7         | D11             |

Connect LCD power, ground, and contrast according to the LCD module requirements.

### 3. Relay Module to Arduino Uno

| Relay Connection | Arduino Uno                                  |
| ---------------- | -------------------------------------------- |
| Control input    | D7                                           |
| GND              | GND                                          |
| VCC              | According to the relay module specifications |

The Arduino sends a control signal to the relay module to switch the pump.

**Safety:** Verify whether the relay module is active-HIGH or active-LOW before connecting the pump. The current Arduino code assumes active-HIGH operation. Test the relay with the actual pump disconnected first.

### 4. Arduino Uno to ESP8266 NodeMCU — UART

| Arduino Uno | ESP8266 NodeMCU                                                    | Purpose                                  |
| ----------- | ------------------------------------------------------------------ | ---------------------------------------- |
| D2 (RX)     | D7 / GPIO13 (TX)                                                   | NodeMCU sends commands to Arduino        |
| D3 (TX)     | D6 / GPIO12 (RX), through a voltage divider or logic-level shifter | Arduino sends sensor readings to NodeMCU |
| GND         | GND                                                                | Common ground                            |

**Important voltage warning:** The Arduino Uno uses 5 V logic, while the ESP8266 uses 3.3 V logic. Never connect Arduino D3 directly to NodeMCU D6. Use a suitable voltage divider or logic-level shifter.

Power the NodeMCU through USB or an appropriate regulated power supply. Connect the grounds of both boards together.

---

## ⚙️ Automatic Irrigation Logic

The Arduino reads the soil moisture sensor and compares the reading with a threshold.

The current code uses a threshold of **900**.

| Soil Sensor Reading | Automatic Pump Action |
| ------------------- | --------------------- |
| 900–1023            | Pump ON               |
| 0–899               | Pump OFF              |

The logic assumes that higher sensor readings indicate drier soil. Actual sensor readings depend on the sensor type, soil conditions, and calibration.

**Note:** Calibrate the sensor before using the system with plants. Do not assume that the threshold of 900 is suitable for every sensor.

---

## 🔄 UART Communication Protocol

The Arduino Uno and NodeMCU exchange simple text messages at **9600 baud**.

### Arduino Uno to NodeMCU

Example message:

```text
SOIL:850
```

The number represents the analog soil moisture sensor reading.

The Arduino sends the reading approximately once per second.

### NodeMCU to Arduino Uno

| UART Message | Function                               |
| ------------ | -------------------------------------- |
| `PUMP_ON`    | Requests manual pump ON                |
| `PUMP_OFF`   | Requests manual pump OFF               |
| `AUTO`       | Returns pump control to automatic mode |

The Arduino receives these messages and updates its pump control mode.

---

## ☁️ Blynk Cloud Configuration

Blynk Cloud provides the online dashboard and communication between the NodeMCU and the remote user interface.

### Template Configuration

Create a template in Blynk Console with these settings:

| Setting       | Value                   |
| ------------- | ----------------------- |
| Template Name | Smart Irrigation System |
| Hardware      | ESP8266                 |
| Connectivity  | Wi-Fi                   |

### Virtual Datastreams

Create the following virtual datastreams:

| Virtual Pin | Data Type | Minimum | Maximum | Purpose                |
| ----------- | --------- | ------: | ------: | ---------------------- |
| V0          | Integer   |       0 |    1023 | Soil moisture reading  |
| V1          | Integer   |       0 |       1 | Manual pump control    |
| V2          | Integer   |       0 |       1 | Automatic mode command |

### Dashboard Widgets

Configure the dashboard with these widgets:

* **Value Display:** Connected to V0 to show the soil sensor reading.
* **Switch:** Connected to V1 to send manual pump ON/OFF commands.
* **Button or Switch:** Connected to V2 to send the automatic mode command.

Configure V1 to send `0` when OFF and `1` when ON.

When V2 sends `1`, the NodeMCU sends the `AUTO` command to the Arduino. The Arduino then returns to automatic pump control based on the soil moisture threshold.

Official Blynk documentation: https://docs.blynk.io/

---

## 📱 Blynk Mobile Application

The Blynk IoT mobile application can provide remote monitoring and control after the device and dashboard have been configured.

### Mobile App Functions

* View the soil moisture sensor reading.
* Send a manual pump ON command.
* Send a manual pump OFF command.
* Return the system to automatic irrigation mode.

### Mobile App Setup

1. Install the official Blynk IoT mobile application.
2. Sign in using the same account used for Blynk Cloud.
3. Open the Smart Irrigation System device.
4. Open the device dashboard.
5. View the soil moisture reading and use the configured pump control widgets.

**Note:** Mobile control requires the NodeMCU to be connected to Wi-Fi and Blynk Cloud, and the UART connection to the Arduino must be working correctly.

---

## 🚀 Installation and Setup

### Step 1: Install Arduino IDE

Install Arduino IDE on your computer.

### Step 2: Install the ESP8266 Board Package

In Arduino IDE, open Boards Manager and install the ESP8266 board package.

Select the appropriate NodeMCU ESP8266 board under **Tools → Board**.

### Step 3: Install the Blynk Library

Open **Sketch → Include Library → Manage Libraries**.

Search for `Blynk` and install the Blynk library.

### Step 4: Configure Blynk

Create the Smart Irrigation System template and configure virtual datastreams V0, V1, and V2 as described above.

Obtain the Template ID and Auth Token for your device.

### Step 5: Configure NodeMCU Credentials

Open:

`ESP8266_Node_mcu/ESP8266_Node_mcu.ino`

Enter your own Wi-Fi and Blynk credentials in the appropriate fields.

**Security:** Do not publish your actual Wi-Fi password or Blynk Auth Token in a public GitHub repository. Keep private credentials out of committed source code.

### Step 6: Upload Arduino Uno Code

Open:

`Arduino_Uno/Smart_Irrigation_Arduino.ino`

Select Arduino Uno in Arduino IDE and upload the sketch.

### Step 7: Upload NodeMCU Code

Open:

`ESP8266_Node_mcu/ESP8266_Node_mcu.ino`

Select the appropriate NodeMCU board and port, then upload the sketch.

### Step 8: Connect the Hardware

Connect the soil sensor, LCD, relay module, and UART wires according to the connection tables above.

Check the voltage levels and common ground before powering the boards.

### Step 9: Test the Complete System

Test the soil sensor readings, LCD display, relay operation, UART communication, Wi-Fi connection, Blynk dashboard, and manual and automatic pump controls.

---

## 🧪 Testing Checklist

Use this checklist when testing the complete project.

* [ ] Soil moisture sensor produces readings.
* [ ] LCD displays the sensor reading.
* [ ] Relay responds to automatic pump control.
* [ ] Arduino Uno and NodeMCU communicate through UART.
* [ ] NodeMCU connects to Wi-Fi.
* [ ] NodeMCU connects to Blynk Cloud.
* [ ] Soil readings appear in the Blynk dashboard.
* [ ] Manual pump ON command works.
* [ ] Manual pump OFF command works.
* [ ] Automatic mode works after sending the `AUTO` command.
* [ ] Mobile app controls work as expected.
* [ ] Relay and pump power connections have been checked safely.

---

## 🔐 Safety and Security

* Never connect Arduino Uno's 5 V TX signal directly to ESP8266 RX.
* Use a suitable voltage divider or logic-level shifter for UART signals from Arduino to NodeMCU.
* Verify the relay module's active-HIGH or active-LOW behavior.
* Test relay operation with the pump disconnected before connecting the pump power supply.
* Use an appropriate power supply for the pump and microcontrollers.
* Do not publish Wi-Fi passwords or Blynk Auth Tokens in a public repository.

---

## 🔮 Future Improvements

* Calibrate soil moisture thresholds for different soil conditions.
* Add temperature and humidity monitoring.
* Add pump status feedback to the dashboard.
* Improve Wi-Fi reconnection handling.
* Add low-water-level detection.
* Add notifications when the soil becomes dry.
* Improve the mobile dashboard with additional sensor information.

---

## 👨‍💻 Author

**K Sabari**

* GitHub: https://github.com/sabarikumar2004
* LinkedIn: https://www.linkedin.com/in/sabarikumar48

---

## 📌 Project Status

The project source code and integration design are prepared for Arduino Uno, ESP8266 NodeMCU, UART communication, and Blynk IoT.

The complete system should be considered operational only after the hardware, Wi-Fi connection, Blynk Cloud, mobile app, and pump controls have been tested successfully.
