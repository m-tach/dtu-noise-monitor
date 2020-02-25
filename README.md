# dtu-noise-monitor
Design of a noise monitor (phonometer), implemented on an Arduino-based microprocessor


## Hardware 
Board description files can be found here: https://learn.sodaq.com/Boards/Sara_AFF/

## Software
1. C using [Atmel Studio 7](https://www.microchip.com/mplab/avr-support/atmel-studio-7) configured for the AVR dude toolchain (see how to [here](https://slightlyovercomplicated.com/2015/11/13/programming-arduino-with-atmel-studio-7/))

2. C using ARDUINO IDE:  
 - board files available at https://raw.githubusercontent.com/SodaqMoja/Sodaq_boards/master/package_sodaq_index.json

## How to contribute to this project:
For this project, we use modular development, to enable collaboration and reduce technical debt over time. This means that we employ [SRP](https://en.wikipedia.org/wiki/Single_responsibility_principle) for each new feature/functionality of the noise monitor. Bellow are the guidelines of how to implement an example feature for the project. 

User story: "I want to extend the current functionality to use the on-board GPS chip to read GPS coordinates".
1. Create a new folder in `noise-monitoring/libraries` called GPSController
2. Inside `noise-monitoring/libraries/GPSController` add two files: GPSController.h and GPSController.c
3. Edit each file, following the templates from the `documentation` folder (called `ExampleController.h` and `ExampleController.c`).
4. In the `main` sketch, include library `GPSController.h`.
5. In the `loop()` of the `main` sketch, call the functions you need from the `GPSController.h`.

## Useful links/tutorials
- https://thingsboard.io/docs/user-guide/integrations/sodaq/
- https://github.com/SodaqMoja/Sodaq_Universal_Tracker


