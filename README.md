# dtu-noise-monitor
Design of a noise monitor (phonometer), implemented on an Arduino-based microprocessor, which maps real-time noise data on a remote maps server.

## Hardware 
- Board: [SODAQ SARA AFF N211](https://learn.sodaq.com/Boards/Sara_AFF/) 
- Microphone: [Grove - Sound Sensor](http://wiki.seeedstudio.com/Grove-Sound_Sensor/)
- Battery: TODO   

**NOTE**: technical documents are uploaded to the [documentation](documentation/) folder.

## Software
1. Embedded: C using ARDUINO IDE; repository with example board files available [here](https://github.com/sodaqmoja)

3. Server: TODO

## Solution structure
//TODO

## How to use test program:
1. Upload main.ino sketch to board
2. Open Serial Monitor in Arduino IDE (Ctrl + Shift + M)
3. Send an ENTER key
4. Navigate through menu by choosing options (similar to DOS)
5. While reading, on-board LED will flash BLUE; while waiting for you to select an option, it will be RED
6. You can stop interrupt by sending a "Q"


## How to contribute to this project:
For this project, we use modular development, to enable collaboration and reduce technical debt over time. This means that we employ [SRP](https://en.wikipedia.org/wiki/Single_responsibility_principle) for each new feature/functionality of the noise monitor. Bellow are the guidelines of how to implement an example feature for the project. 

User story: "I want to extend the current functionality to use the on-board GPS chip to read GPS coordinates".
1. Create a new folder in `noise-monitoring/libraries` called GPSController
2. Inside `noise-monitoring/libraries/GPSController` add two files: GPSController.h and GPSController.cpp
3. Edit each file, following the templates from the `documentation` folder (called `ExampleController.h` and `ExampleController.cpp`).
4. In the `main` sketch, include library `GPSController.h`.
5. In the `loop()` of the `main` sketch, call the functions you need from the `GPSController.h`.


## Communication
The current data package is as defined in [Message.h](libraries/Message/Message.h):
```c
struct NoiseMonitorMessage
{
	uint32_t timestamp;
	uint8_t batteryVoltage;
	int8_t boardTemperature;
	uint32_t latitude;
	uint32_t longitude;
	float noiseLevel;
};
```


## Useful links/tutorials
- https://thingsboard.io/docs/user-guide/integrations/sodaq/
- https://github.com/SodaqMoja/Sodaq_Universal_Tracker
- http://wiki.seeedstudio.com/Grove-Sound_Sensor/


