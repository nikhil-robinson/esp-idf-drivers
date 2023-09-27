# DS1307_RTC Example Project

This is an example project demonstrating the usage of the TinyRTC with the associated libraries and code.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)


## Introduction

This project showcases how to interface with the TinyRTC using the provided libraries and main code. The Tiny RTC module combines both the DS1307 RTC and the AT24C32 EEPROM on a single board

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

## Usage

To use this project, follow these steps:

1. Connect your TinyRTC to your hardware setup.
2. Modify the `main.c` file to suit your specific requirements.
3. Build and flash the code onto your target device.

Ensure that you have a good understanding of your hardware setup and the TinyRTC(ds1307) datasheet for proper usage.

## Contributing

If you would like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and test them thoroughly.
4. Create a pull request with a clear description of your changes.
