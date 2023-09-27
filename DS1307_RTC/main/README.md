# Tiny RTC (DS1307 and AT24C32) Example

This project demonstrates how to interface with the Tiny RTC module, which combines a DS1307 Real-Time Clock (RTC) and an AT24C32 EEPROM on an ESP32 microcontroller using the ESP-IDF framework. It enables the initialization, writing of time data to and reading from the DS1307 RTC, as well as the storage and retrieval of data to and from the AT24C32 EEPROM via the I2C communication protocol.

## Table of Contents

- [Installation](#installation)
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
