# IoT-Based Smart Irrigation System 🌱

<p align="center">
  <img src="Image/project_thumbnail.png" alt="IoT-Based Smart Irrigation System using ATmega328P, ESP8266, and Blynk" width="100%">
</p>

<p align="center">
  <b>Automated Irrigation | Soil Moisture Monitoring | Wi-Fi Connectivity | Remote Pump Control</b>
</p>

## 📌 Project Overview

The IoT-Based Smart Irrigation System is an embedded systems project designed to automate plant watering based on soil moisture levels.

The system uses an Arduino Uno based on the ATmega328P microcontroller to read analog soil moisture sensor data, process the readings, display the soil condition on a 16×2 LCD, and control a water pump through a relay module.

An ESP8266 Wi-Fi module is intended to provide internet connectivity for sending sensor readings and pump status to Blynk IoT Cloud. Cloud monitoring and remote pump control require additional firmware implementation and testing.

This project demonstrates embedded C/C++ programming, analog sensor interfacing, ADC, GPIO control, LCD interfacing, relay control, UART communication, and IoT connectivity.

## 🎯 Project Objectives

* Monitor soil moisture using an analog sensor.
* Automate water pump operation based on soil moisture thresholds.
* Display soil moisture readings and soil conditions on a 16×2 LCD.
* Interface an ESP8266 Wi-Fi module with the Arduino Uno.
* Extend the system with Blynk IoT Cloud monitoring.
* Add remote pump control and automatic/manual operating modes.

## 🛠️ Hardware Requirements

| Component                   | Purpose                                     |
| --------------------------- | ------------------------------------------- |
| Arduino Uno (ATmega328P)    | Main microcontroller                        |
| Soil Moisture Sensor        | Measures soil moisture                      |
| 16×2 LCD                    | Displays sensor readings and soil condition |
| Relay Module                | Switches the water pump                     |
| Water Pump                  | Supplies water for irrigation               |
| ESP8266 ESP-01              | Wi-Fi connectivity                          |
| Regulated 3.3V Power Supply | Powers the ESP8266                          |
| Suitable Pump Power Supply  | Powers the water pump                       |
| Jumper Wires                | Electrical connections                      |
| Breadboard                  | Circuit prototyping                         |

## 💻 Software and Technologies

* Embedded C/C++ for Arduino
* Arduino IDE
* ATmega328P Microcontroller
* Analog-to-Digital Conversion (ADC)
* General-Purpose Input/Output (GPIO)
* LCD Interfacing
* Relay Interfacing
* UART Serial Communication
* ESP8266 Wi-Fi Module
* Blynk IoT Platform
* AT Commands for ESP8266 communication

## 🔌 Pin Connections

### Arduino Uno Connections

| Component            | Component Pin | Arduino Uno Pin                                |
| -------------------- | ------------- | ---------------------------------------------- |
| Soil Moisture Sensor | AO            | A0                                             |
| LCD                  | RS            | D13                                            |
| LCD                  | EN            | D12                                            |
| LCD                  | D4            | D8                                             |
| LCD                  | D5            | D9                                             |
| LCD                  | D6            | D10                                            |
| LCD                  | D7            | D11                                            |
| Relay Module         | IN            | D7                                             |
| ESP8266              | TX            | D2 (SoftwareSerial RX)                         |
| ESP8266              | RX            | D3 (SoftwareSerial TX, through level shifting) |

### ESP8266 ESP-01 Power Connections

| ESP8266 Pin | Connection                                      |
| ----------- | ----------------------------------------------- |
| VCC         | Regulated 3.3V supply                           |
| GND         | Common ground                                   |
| EN/CH_PD    | 3.3V                                            |
| RST         | 3.3V through an appropriate pull-up arrangement |
| GPIO0       | HIGH during normal boot                         |
| GPIO2       | HIGH during normal boot                         |

**Important electrical precautions:**

* The ESP8266 uses 3.3V logic.
* Do not connect the Arduino Uno's 5V TX signal directly to the ESP8266 RX pin. Use a suitable logic-level shifter or voltage divider.
* Use a regulated 3.3V supply capable of handling the ESP8266's current peaks.
* Connect the Arduino and ESP8266 grounds together.
* Confirm the ESP8266 module pinout before making connections.

The ESP8266 connections above apply to the ESP-01 module. Other ESP8266 development boards may require different connections.

## ⚙️ Working Principle

### 1. Soil Moisture Sensing

The soil moisture sensor produces an analog signal corresponding to the soil condition. The Arduino Uno reads the signal through analog pin A0 using its built-in ADC.

The ATmega328P provides a 10-bit ADC, producing readings from 0 to 1023.

### 2. Soil Condition Classification

The sensor reading is compared against predefined thresholds to classify the soil condition.

| Sensor Reading | Soil Condition   | Pump Action |
| -------------- | ---------------- | ----------- |
| 900–1023       | Dry Soil         | ON          |
| 600–899        | Slightly Moist   | OFF         |
| 300–599        | Wet Soil         | OFF         |
| 0–299          | Very Wet / Water | OFF         |

These are initial example thresholds. Actual readings depend on the sensor, soil type, and calibration. Adjust the thresholds according to real sensor measurements.

### 3. Automatic Water Pump Control

The Arduino processes the sensor reading and controls the relay module.

* When the sensor reading reaches the configured dry-soil threshold, the pump is switched ON.
* When the sensor reading falls below the dry-soil threshold, the pump is switched OFF.

The relay provides a switching interface between the microcontroller and the pump circuit.

**Safety:** Use an appropriately rated relay and a suitable power supply for the pump. Do not power the pump directly from an Arduino GPIO pin.

### 4. LCD Display

A 16×2 LCD displays the soil moisture reading and the corresponding soil condition or pump status.

### 5. ESP8266 Wi-Fi Communication

The ESP8266 can provide wireless connectivity to the system. The Arduino can communicate with the ESP8266 using UART serial communication.

The ESP8266 must be configured with suitable firmware and network settings before it can exchange data with an IoT cloud platform.

### 6. Blynk IoT Integration

The planned Blynk integration can provide a mobile dashboard for displaying soil moisture readings and pump status.

Remote pump operation requires cloud-to-device communication and firmware that processes remote commands. Automatic/manual mode selection also requires additional control logic.

These functions must be implemented and tested before they can be considered operational.

## 📊 System Architecture

```text
Soil Moisture Sensor
        |
        | Analog Signal
        v
   Arduino Uno
    ATmega328P
        |
        +------------------+
        |                  |
        v                  v
     16×2 LCD          Relay Module
                            |
                            v
                        Water Pump

   Arduino Uno
        |
        | UART
        v
     ESP8266
        |
        | Wi-Fi
        v
   Blynk IoT Cloud
        |
        v
   Blynk Mobile App
```

The sensor, LCD, and relay are part of the basic Arduino control system. The cloud and mobile-app functions depend on completing the ESP8266 and Blynk firmware integration.

## 🌐 Planned IoT Features

The intended IoT implementation includes:

* Live soil moisture monitoring.
* Cloud-based display of soil condition.
* Remote monitoring of pump status.
* Automatic irrigation based on sensor readings.
* Manual pump control through the Blynk application.
* Automatic/manual operating mode selection.

**Implementation status:** The original Arduino code implements soil moisture reading, LCD display, and automatic relay control. ESP8266 cloud communication, remote pump control, and automatic/manual mode selection require further implementation and testing.

## 🧠 Embedded Systems Concepts Demonstrated

* Analog sensor interfacing
* ADC-based sensor measurement
* Threshold-based decision-making
* GPIO input and output control
* Relay interfacing
* LCD interfacing
* UART serial communication
* Microcontroller-based automation
* Embedded firmware development
* Wi-Fi and IoT integration concepts

## 🚀 Future Improvements

* Implement and verify reliable Blynk cloud communication.
* Add remote pump control through the mobile application.
* Implement automatic/manual operating modes.
* Add Wi-Fi disconnection detection and reconnection.
* Introduce hysteresis to reduce frequent pump switching near the threshold.
* Add maximum pump-running time and dry-run protection.
* Improve sensor calibration and moisture measurement accuracy.
* Add temperature and humidity monitoring.
* Add water tank level monitoring.
* Introduce data logging and mobile notifications.
* Explore solar-powered operation.

## 🌱 Applications

* Home gardens
* Agricultural irrigation
* Greenhouses
* Plant nurseries
* Small-scale farming
* Automated plant watering systems

## ✅ Advantages

* Automates the irrigation process.
* Reduces the need for continuous manual monitoring.
* Helps reduce water wastage when properly calibrated.
* Provides a foundation for IoT-based agricultural automation.
* Can be extended with additional sensors and cloud services.

## 👨‍💻 Author

**Sabari**

Embedded Systems / Firmware Engineer Fresher

GitHub: [sabarikumar2004](https://github.com/sabarikumar2004)

LinkedIn: [sabarikumar48](https://www.linkedin.com/in/sabarikumar48)

---

**Technologies:** Arduino Uno | ATmega328P | Embedded C/C++ | ADC | GPIO | LCD | Relay | ESP8266 | UART | Blynk IoT
