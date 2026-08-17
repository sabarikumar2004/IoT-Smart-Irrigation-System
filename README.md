# IoT-Based Smart Irrigation System

## Overview

The IoT-Based Smart Irrigation System is an embedded and IoT project developed to automate the irrigation process based on soil moisture conditions.

In this project, an Arduino Uno with ATmega328P is used as the main controller to monitor the soil moisture level. Based on the soil moisture value, the system automatically controls the water pump.

An ESP8266 is used to provide Wi-Fi connectivity. The system is connected to the Blynk platform, which allows the user to monitor the system remotely and control the water pump.

The main objective of the project is to reduce water wastage and automate the irrigation process.

## Features

* Soil moisture monitoring
* Automatic water pump control
* Arduino Uno based control
* ESP8266 Wi-Fi connectivity
* Blynk-based remote monitoring
* Remote pump control
* Automated irrigation
* Reduced water wastage

## Hardware Components

* Arduino Uno (ATmega328P)
* Soil Moisture Sensor
* ESP8266 Wi-Fi Module
* Relay Module
* Water Pump
* External Power Supply
* Jumper Wires
* Breadboard

## Software and Platforms

* Arduino IDE
* Embedded C / Arduino C
* Blynk IoT Platform

## Working Principle

The soil moisture sensor continuously monitors the moisture level of the soil.

The Arduino Uno reads the soil moisture value and uses it to determine whether irrigation is required.

### Dry Soil

When the soil moisture level indicates that the soil is dry:

Soil Moisture Sensor
        ↓
Arduino Uno
        ↓
Low Soil Moisture Detected
        ↓
Relay Activated
        ↓
Water Pump ON
        ↓
Water Supplied to Soil


### Sufficient Soil Moisture

When sufficient moisture is detected:


Soil Moisture Sensor
        ↓
Arduino Uno
        ↓
Sufficient Moisture Detected
        ↓
Relay Deactivated
        ↓
Water Pump OFF

## IoT Functionality

The ESP8266 provides Wi-Fi connectivity to the system.

Through the Blynk platform, the user can remotely monitor the irrigation system and control the water pump.

Arduino Uno
     │
     ▼
ESP8266
     │
     │ Wi-Fi
     ▼
Blynk Platform
     │
     ├── Monitor System
     │
     └── Control Water Pump

## System Block Diagram

``
                 ┌──────────────────────┐
                 │  Soil Moisture       │
                 │      Sensor          │
                 └──────────┬───────────┘
                            │
                            ▼
                 ┌──────────────────────┐
                 │     Arduino UNO      │
                 │      ATmega328P      │
                 └──────────┬───────────┘
                            │
                    ┌───────┴────────┐
                    │                │
                    ▼                ▼
             ┌────────────┐   ┌──────────────┐
             │   Relay    │   │   ESP8266    │
             └─────┬──────┘   │ Wi-Fi Module │
                   │          └───────┬──────┘
                   ▼                  │
             ┌────────────┐           │ Wi-Fi
             │ Water Pump │           ▼
             └────────────┘     ┌─────────────┐
                                │    Blynk    │
                                │  Platform   │
                                └─────────────┘


## Applications

The system can be used for:

* Home gardens
* Agricultural irrigation
* Greenhouses
* Plant nurseries
* Small-scale farming
* Automated plant watering systems

## Advantages

* Reduces water wastage
* Automates the irrigation process
* Reduces manual effort
* Enables remote monitoring
* Allows remote pump control
* Simple and scalable embedded system

## Future Improvements

The project can be further improved by adding:

* Temperature and humidity monitoring
* Water tank level monitoring
* Weather-based irrigation
* Mobile notifications
* Multiple irrigation zones
* Data logging
* Solar-powered operation



## Project Technologies

* Arduino Uno
* ATmega328P
* ESP8266
* Soil Moisture Sensor
* Relay Module
* Water Pump
* Wi-Fi
* Blynk
* Embedded C / Arduino C

## Author

Sabari

Embedded Systems / Firmware Engineer Fresher
