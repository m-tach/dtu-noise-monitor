#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

#include "Arduino.h"

#define WIRE_BUS 1
#define SERIAL_BUS 2

#define GPS_INTERFACE WIRE_BUS 

#if (GPS_INTERFACE == WIRE_BUS)
  #include <Wire.h>
  #define GPS_STREAM Wire
  #define GPS_ADR 0x42
#elif (GPS_INTERFACE == SERIAL_BUS)
  #define GPS_STREAM Serial
  #define GPS_BAUD 57600
#else
  #error "Invalid GPS_INTERFACE"
#endif

#define CONSOLE_STREAM SerialUSB
#define CONSOLE_BAUD 9600

#define READ_TIMEOUT_MS 100

#define BUFFER_SIZE 256

#endif


class gpsCtlr
{
   public:
   gpsCtlr();                      //Including enable operation
   ~gpsCtlr();
   //void gpsEnable(bool state);
   size_t readGPS();
   size_t readConsole();
   size_t readUbloxI2cStream();
   size_t readSerialStream(Stream* stream);
   void writeGPS(size_t count);
   void writeConsole(size_t count);
  // private:
   
};

