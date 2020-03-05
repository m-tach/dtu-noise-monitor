#include "gpsController.h"
#include "CommunicationController.h"
gpsCtlr gpsCtlr;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  //THIS DEFINATION SHOULD BE HERE, COULD NOT BE REMOVED TO CONSTRUCTION FUNCTION
  #if (GPS_INTERFACE == WIRE_BUS)
     Wire.begin();
  #elif (GPS_INTERFACE == SERIAL_BUS)
    GPS_STREAM.begin(GPS_BAUD);
  #endif

    CONSOLE_STREAM.begin(CONSOLE_BAUD);
}
void loop() {
  // put your main code here, to run repeatedly:
  test_function();
  gpsCtlr.writeGPS(gpsCtlr.readConsole());
  //GPS -> Console
  gpsCtlr.writeConsole(gpsCtlr.readGPS());
}
