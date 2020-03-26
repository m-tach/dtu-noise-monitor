/**
 * @file Contains main loop for Arduino sketch for noise-monitor.
 */

#include "Arduino.h"
#include <CommunicationController.h>
#include <MicrophoneController.h>
#include <Message.h>


void setup() 
{
  initCommunication();
  initADC();
}

void loop() 
{
  sendMessage("Enter loop \n");
  //create string buffer to transmit over USB
  char buffer[80];
  //instantiate message with all values set to 0
  NoiseMonitorMessage* message; 
  //read noise level from MicrophoneController
  message->noiseLevel = readADC();
  //TODO: read other things
  //convert message to string
  serialize(message, buffer);
  //transmit string over USB
  sendMessage(buffer);

  //TODO: free up memory
  systemSleep();

  sendMessage("Exit loop \n");
}
