#include <CommunicationController.h>
#include "Arduino.h"

/**
 * Contains main loop for Arduino sketch for noise-monitor.
 */

void setup() {
  // put your setup code here, to run once:
  initUSBDriver();
}

void loop() {
  //transmit "Hello World" to serial port
  sendMessage("Hello World");
  
}
