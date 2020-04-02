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
  sendMessage("\n Enter loop \n");
  char buffer[512]; //create string buffer to transmit over USB
  NoiseMonitorMessage message = {0, 0, 0, 0, 0, 0.0}; //instantiate message with all values set to 0
  message.noiseLevel = readADC(); //read noise level from MicrophoneController
  //TODO: read other things and populate message
  message2Char(&message, buffer); //convert message to string
  sendMessage(buffer);  //transmit string over USB
  systemSleep(); //sleep - from Vittorio's code - i don't know why
  //TODO: free up buffer to avoid memory leaks
  sendMessage("Exit loop\n");
}
