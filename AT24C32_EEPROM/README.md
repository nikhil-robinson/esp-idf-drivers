# AT24C32_EEPROM Example Project

This AT24C32 Example Project demonstrates how to interface with the AT24C32 EEPROM using the ESP-IDF framework on target (ESP32 , ESP32-S2, ESP32-S3 or ESP32-C3) microcontroller, allowing for the initialization, reading, and writing of data to the EEPROM via the I2C communication protocol.

## Table of Contents

- [Installation](#installation)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Getting Started](#getting-started)
- [Hardware Required](#hardware-required)
- [Usage](#usage)
- [Example Output](#example-output)

## Installation 

1. Clone this repository to your local development environment.

```
git clone https://github.com/nikhil-robinson/esp-idf-drivers.git
```
2. Navigate to the Project Directory
```
cd AT24C32_EEPROM
```
3. Configure the project using the ESP-IDF command-line tool.
```
idf.py menuconfig
```
4. Build and flash the project to your Target(ESP32) Microcontroller.

```
idf.py -p /dev/ttyUSB0 flash
```
change /dev/ttyUSB0 to your portname


## Project Structure

The project is organized into the following folders:

- **components:** Contains libraries and dependencies.
- **main:** Contains the main code and CMakeLists.txt for building the project.
- **CMakeLists.txt:** The CMake configuration file for the project.
- **sdkConfig:** Configures build settings for esp-idf projects.

## Dependencies

The project relies on the following libraries:

- **at24c32.h:**  provides functions for interfacing with the AT24C32 EEPROM using the I2C communication protocol. It includes functions for reading and writing data to the EEPROM, as well as initializing the EEPROM device. The library supports different EEPROM sizes and block operations.
- **esp_idf_lib_helpers.h:** library contains utility functions and helpers that facilitate the development of ESP-IDF (Espressif IoT Development Framework) projects. It may include functions related to logging, memory management, or other common tasks to simplify the development process.
- **i2cdev.h:** provides low-level functions for configuring and using I2C devices with ESP-IDF. It may include functions for I2C initialization, data transmission, and other I2C-related operations.

Please make sure to include these libraries before building the project.

## Getting Started

To get started with this project, follow these steps:

1. Clone this repository to your local machine.
2. Install the necessary dependencies (see [Dependencies](#dependencies)).
3. Build the project using CMake.


## Hardware Required

To run this project, you will need the following hardware components:

- **TARGET(ESP32) Microcontroller:** The project is designed to run on the ESP32-S3 microcontroller, which serves as the control unit for interacting with the AT24C32 EEPROM.

- **AT24C32 EEPROM:** The AT24C32 EEPROM is used to store and retrieve data. Ensure proper connections to the ESP32-S3 for power and data communication: 

```
 ----------------------             ------------------
|               SCL(9) |-----------| SCL              |
|                      |           |                  | 
|               SDA(8) |-----------| SDA              |
|   ESP32-S3           |           |        AT24C32   |
|               VCC    |-----------| VCC              |
|                      |           |                  |
|               GND    |-----------| GND              |
 ----------------------             ------------------
```
Connect the SCL and SDA pins of the ESP32-S3 to their corresponding pins on the AT24C32. Additionally, provide power (VCC) and ground (GND) connections to both devices.
To use this project, follow these steps:

Ensure that you have a good understanding of your hardware setup and the AT24C32 datasheet for proper usage.

## Usage

1. **Set Up ESP32 Development Environment:** Ensure you have set up your ESP32 development environment with ESP-IDF. You can refer to the ESP-IDF documentation for installation and setup instructions.

2. **Include Necessary Libraries and Headers:** At the beginning of your project, include the necessary libraries and headers:

```c
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <driver/i2c.h>

#include <esp_log.h>
#include <esp_err.h>

#include <at24c32.h> 

```

3. **Implement the at24c32Test Function:** In your code, implement the at24c32Test function. This function is responsible for initializing the EEPROM, reading data from it, and printing the result.

4. **Modify at24c32Test for Your Project:** Customize the at24c32Test function to suit your specific project requirements. You can use the provided code as a starting point and adapt it as needed.

5. **Create a Task in app_main Function:** In the app_main function, create a task that runs the at24c32Test function.

### Build and Flash

Build the project using the ESP-IDF tools and flash the code onto your ESP32 device.

## Example Output :