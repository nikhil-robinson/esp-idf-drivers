# Tiny RTC (DS1307 and AT24C32) Example

This project demonstrates how to interface with the Tiny RTC module, which combines a DS1307 Real-Time Clock (RTC) and an AT24C32 EEPROM on an ESP32 microcontroller using the ESP-IDF framework. It enables the initialization, writing of time data to and reading from the DS1307 RTC, as well as the storage and retrieval of data to and from the AT24C32 EEPROM via the I2C communication protocol.

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
cd DS1307_RTC
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

- **ds1307.h:** provides functions for facilitating timekeeping and management of the RTC module's features on ESP32 microcontrollers via I2C communication.

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

- **TARGET(ESP32) Microcontroller:** The project is designed to run on the ESP32-S3 microcontroller, which serves as the control unit for interacting with the TinyRTC.

- **TinyRTC:** The Tiny RTC module combines both the DS1307 RTC and the AT24C32 EEPROM on a single board. Ensure proper connections to the ESP32 for power and data communication: 

```
 ----------------------             ------------------
|               SCL(9) |-----------| SCL              |
|                      |           |                  | 
|               SDA(8) |-----------| SDA              |
|   ESP32-S3           |           |        TinyRTC   |
|               VCC    |-----------| VCC              |
|                      |           |                  |
|               GND    |-----------| GND              |
 ----------------------             ------------------

```

Connect the SCL and SDA pins of the ESP32-S3 to their corresponding pins on the TinyRTC. Additionally, provide power (VCC) and ground (GND) connections to both devices.

Ensure that you have a good understanding of your hardware setup and the TinyRTC(ds1307) datasheet for proper usage.

## Usage

1. **Set Up ESP32 Development Environment:** Ensure you have set up your ESP32 development environment with ESP-IDF. You can refer to the ESP-IDF documentation for installation and setup instructions.

2. **Include Necessary Libraries and Headers:** At the beginning of your project, include the necessary libraries and headers:

```c
#include <stdio.h>
#include <i2cdev.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>

#include <esp_log.h>
#include <esp_err.h>

#include <ds1307.h>
#include <at24c32.h>

```

3. **Implement the ds1307_test Function:** In your code, implement the ds1307_test function. This function initializes the DS1307 RTC and AT24C32 EEPROM, reads and displays the time from the DS1307 RTC, and writes the time to the AT24C32 EEPROM.

  - *Uncomment Code to Set the Time (Optional):* In the ds1307_test function, you can uncomment the section that sets the initial time using the following code:

```
/*
struct tm time = {
    .tm_year = 123,    // Set the year (e.g., 2023)
    .tm_mon = 8,       // Set the month (1-12, 1 for January)
    .tm_mday = 19,     // Set the day of the month
    .tm_hour = 11,     // Set the hour (0-23)
    .tm_min = 20,      // Set the minutes (0-59)
    .tm_sec = 30       // Set the seconds (0-59)
};
ESP_ERROR_CHECK(ds1307_set_time(&dev, &time));
*/

```
Customize the values within the ``` struct tm ``` to set the desired initial time. Once set, you can comment out this section to avoid overwriting the time on subsequent runs.

4. **Customize ds1307_test for Your Project:** Customize the ds1307_test function to suit your specific project requirements. You can use the provided code as a starting point and adapt it as needed.

5. **Create a Task in app_main Function:** In the app_main function, create a task that runs the ds1307_test function.

### Build and Flash

Build the project using the ESP-IDF tools and flash the code onto your ESP32 device.

## Example Output :
