# W25Q32_FLASHIC Example

This W25Q32 Flash Memory Example Project demonstrates how to interface with the W25Q32 Flash Memory IC using the ESP-IDF framework on TARGET (ESP32, ESP32-S3 , ESP32-S2 or ESP32-C3) microcontroller. It allows for the initialization, reading, erasing and writing of data to the flash memory via the SPI communication protocol.

## Table of Contents

- [Installation](#installation)
- [Hardware Required](#hardware-required)
- [Usage](#usage)
- [Example Output](#example-output)

## Installation 

1. Clone this repository to your local development environment.

```
git clone https://FarhanaJamal@bitbucket.org/Bihardware/esp-drivers.git 
```
2. Navigate to the Project Directory
```
cd W25Q32_FLASHIC
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

- **TARGET(ESP32) Microcontroller:** The project is designed to run on an ESP32 microcontroller, which serves as the control unit for interacting with the W25Q32 flash memory IC.

- **W25Q32 Flash Memory IC:** The W25Q32 flash memory IC is used to read, write and erase data. Ensure proper connections to the ESP32 for power and data communication using the SPI interface.

```
 ----------------------             ------------------
|              MOSI(11)|-----------| DI               |
|                      |           |                  | 
|              MISO(12)|-----------| DO               |
|   ESP32-S3           |           |        W25Q32    |
|               CS(10) |-----------| CS               |
|                      |           |                  |
|              SCLK(13)|-----------| CLK              |
 ----------------------             ------------------     
  ```

Connect the MOSI ,MISO , SCLK and CS pins of the ESP32-S3 to their corresponding pins on the W25Q32. Additionally, provide power (VCC) and ground (GND) connections to both devices.

## Usage


1. **Set Up ESP32 Development Environment:** Ensure you have set up your ESP32 development environment with ESP-IDF. You can refer to the ESP-IDF documentation for installation and setup instructions.

2. **Include Necessary Libraries and Headers:** At the beginning of your project, include the necessary libraries and headers:

```c
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "w25q32.h"

#define TAG "W25Q32"

```

3. **Review and Customize the Code:** In the provided ```app_main``` function, the code demonstrates various operations on the W25Q32 flash memory IC, such as reading ,erasing and writing data, reading status registers, and reading the manufacturer's unique ID. Customize the code to suit your specific project requirements.

### Build and Flash

Build the project using the ESP-IDF tools and flash the code onto your ESP32 device.

## Example Output :