#include <CommunicationController.h>
#include "Arduino.h"

/**
 * Contains main loop for Arduino sketch for noise-monitor.
 */

void setup() 
{
  initUSBDriver();
}

void loop() 
{
  //transmit "Hello World" to anyone, monitoring the serial port
  sendMessage("Hello World/n");
}
