# AT24C32_EEPROM Example

This AT24C32 Example Project demonstrates how to interface with the AT24C32 EEPROM using the ESP-IDF framework on target (ESP32 , ESP32-S2, ESP32-S3 or ESP32-C3) microcontroller, allowing for the initialization, reading, and writing of data to the EEPROM via the I2C communication protocol.

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
<<<<<<< HEAD
 
 ```
=======
```
>>>>>>> 0cb15a3dcc2a42854f61b029de5d9489b6d2270f

Connect the SCL and SDA pins of the ESP32-S3 to their corresponding pins on the AT24C32. Additionally, provide power (VCC) and ground (GND) connections to both devices.

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
