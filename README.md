## The Biotemp Instrumentation System

The Biotemp Instrumentation System is a user-friendly IoT device designed for collecting room temperature data. It is made to be effortless to set up and use, in a plug-and-play manner. Equipped with menus displayed on an LCD screen, it offers a straightforward interface for users to access and manage temperature information effectively.

## Functional Diagram

The Biotemp system is composed of different modules that serve the separation of concerns between the different featured functionalities.
It is designed for monitoring and managing temperature data using an ESP32 microcontroller. It consists of several modules that work together to provide a comprehensive temperature monitoring solution.

![Biotemp Function Diagram](./assets/Biotem-diagram-Top%20View.png)

## Modules

### 1. Config Module

The Config Module is responsible for managing the configuration settings of the Biotemp system. It allows the hard parameter configuration and it is responsible for kickstarting the main loop of the firmware. Also it runs the testing facilities that can self-validate the hardware normal operation.

### 2. Data Storage Module

The Data Storage Module handles the storage and retrieval of temperature data collected by the ESP32. To cluster the changing states into a easy-to-decouple strategy handler. It also manages the communication with the external broker to persist the data.

### 3. System Testing Module

The System Testing Module provides functionalities for testing the integrity and reliability of the Biotemp system. It includes features for self-diagnosis, sensor calibration, and connectivity testing to ensure the system operates correctly and can be utilized.

### 4. Temperature Module

The Temperature Module is the core component of the Biotemp software. It interfaces with temperature sensors connected to the ESP32 to continuously monitor environmental temperatures. This module processes the raw sensor data, applies any necessary corrections, and communicates with other modules for data storage and analysis.

## How to Build It?

The Biotemp firmware is developed for the ESP32 microcontroller using PlatformIO. To recreate the project, follow these steps:

1. Clone the Biotemp repository from GitHub.
2. Open the project folder in your preferred IDE.
3. Ensure that PlatformIO is installed and configured.
4. Open the `platformio.ini` file and verify the configuration settings, including the target board and libraries.
5. Compile and upload the firmware to your ESP32 device using PlatformIO.

## Usage

To use Biotemp, follow these general steps:

1. Configure the system settings using the Config Module.
2. Deploy the ESP32 device in the desired location for temperature monitoring.
3. Monitor temperature data using the Data Storage Module.
4. Perform system tests periodically using the System Testing Module.
5. Analyze temperature trends and patterns for insights into environmental conditions.
