#include <CommunicationController.h>
#include <MicrophoneController.h>
#include "Arduino.h"

/**
 * Contains main loop for Arduino sketch for noise-monitor.
 */

void setup() 
{
  initCommunication();
}

void loop() 
{
  //transmit "Hello World" to anyone, monitoring the serial port
  sendMessage("Hello World/n");
}
