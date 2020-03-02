#ifndef gpsController_h
#define gpsController_h
#include <gpsController.h>
#endif

gpsCtlr gpsCtlr;
void setup() {
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:
  gpsCtlr.writeGPS(gpsCtlr.readConsole());
  //GPS -> Console
  gpsCtlr.writeConsole(gpsCtlr.readGPS());
}
