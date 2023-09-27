# AT24C32 Example Project

This is an example project demonstrating the usage of the AT24C32 EEPROM with the associated libraries and code.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)


## Introduction

This project showcases how to interface with the AT24C32 EEPROM using the provided libraries and main code. The AT24C32 is a popular I2C EEPROM commonly used in embedded systems.

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

## Usage

To use this project, follow these steps:

1. Connect your AT24C32 EEPROM to your hardware setup.
2. Modify the `main.c` file to suit your specific requirements.
3. Build and flash the code onto your target device.

Ensure that you have a good understanding of your hardware setup and the AT24C32 datasheet for proper usage.

## Contributing

If you would like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and test them thoroughly.
4. Create a pull request with a clear description of your changes.
