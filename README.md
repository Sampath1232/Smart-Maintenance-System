# Smart Maintenance System

An IoT-based predictive maintenance and safety monitoring system built using Arduino Mega 2560 to automate hazard detection and reduce manual inspection in industrial and household environments.

## Overview

Traditional maintenance systems require regular manual inspections, which can be time-consuming and risky in hazardous conditions. This project automates maintenance monitoring by using multiple sensors to detect environmental and safety issues such as gas leaks, fire, water leakage, temperature changes, and harmful gas presence.

The system sends real-time alerts to a smartphone via Bluetooth for quick action.

## Features

* Real-time flammable gas detection
* Harmful gas monitoring
* Fire and flame detection
* Water leakage detection
* Temperature and humidity monitoring
* Bluetooth-based alert notifications
* Solar panel light tracking using LDR and Servo Motors
* Battery-powered portable operation

## Components Used

* Arduino Mega 2560
* HC-05 Bluetooth Module
* MQ-2 Gas Sensor
* MQ-135 Gas Sensor
* Water Flow Sensor
* Flame Sensor
* DHT-11 Temperature and Humidity Sensor
* Solar Panel
* Servo Motors
* Water Pump
* Lead Acid Battery
* LDR Sensors

## Working Principle

The system continuously monitors environmental conditions using multiple sensors connected to the Arduino Mega 2560.

### Sensor Functions

### MQ-2 Sensor

Detects:

* LPG
* Butane
* Propane
* Hydrogen
* Smoke

### MQ-135 Sensor

Detects:

* Ammonia
* Alcohol
* Sulphides
* Benzene
* Air pollutants

### Flame Sensor

Detects fire using infrared sensing.

### DHT-11 Sensor

Monitors:

* Temperature
* Humidity

### Water Flow Sensor

Monitors water flow and leakage.

### LDR + Servo Motors

Tracks sunlight direction and adjusts solar panels for better efficiency.

### HC-05 Bluetooth Module

Sends real-time alerts to connected smartphones.

## Alert Messages

The system generates alerts such as:

* Flammable Gas Detected
* Harmful Gas Detected
* Fire Detected
* Water Leakage Detected
* High Temperature Detected
* High Humidity Detected

## Technologies Used

* Arduino IDE
* Embedded C/C++
* Sensor Integration
* Bluetooth Communication
* IoT Monitoring
* Solar Tracking Automation

## Advantages

* Reduces manual maintenance effort
* Improves safety in hazardous environments
* Saves time
* Faster incident detection
* Low-cost implementation
* Portable and easy to maintain

## Applications

* Industrial safety systems
* Smart homes
* Fire safety systems
* Water monitoring systems
* Gas leakage detection
* Chemical industries

## Future Improvements

* Cloud-based monitoring
* Mobile application integration
* Automatic fire suppression
* Intruder detection system
* Smart load monitoring

## Academic Information

Institution: Acharya Polytechnic
Department: Mechatronics Engineering
Academic Year: 2020–2021

## License

This project is created for educational and research purposes.
