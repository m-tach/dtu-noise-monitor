/**
 * @file Contains main loop for Arduino sketch for noise-monitor.
 */

#include "Arduino.h"
#include <CommunicationController.h>
#include <MicrophoneController.h>
#include <Message.h>
#include <Sodaq_UBlox_GPS.h>


void setup() 
{
  initCommunication();
  initADC();
  sodaq_gps.init(GPS_ENABLE);
}

void loop() 
{
  sendMessage("Enter loop \n");

  if (sodaq_gps.scan(true))
  {
    char buffer[512]; //create string buffer to transmit over USB
    char timestampBuffer[64];
    NoiseMonitorMessage message = {0, 0, 0, 0, 0, 0.0}; //instantiate message with all values set to 0
    message.noiseLevel = readADC(); //read noise level from MicrophoneController

    message.latitude = sodaq_gps.getLat();
    message.longitude = sodaq_gps.getLon();
    strncpy(timestampBuffer, sodaq_gps.getDateTimeString().c_str(), sizeof(timestampBuffer));
    strncpy(message.timestamp, timestampBuffer, 64);
    message2Char(&message, buffer); //convert message to string
    sendMessage(buffer);  //transmit string over USB
    
    //systemSleep(); //sleep - from Vittorio's code - i don't know why
    //TODO: free up buffer to avoid memory leaks
  } else {
    sendMessage("GPS is not connected; Wait 1s...\n");
    delay(1000);      
  }  
  sendMessage("Exit loop \n");

}
