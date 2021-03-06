/**
* @file Contains main loop for Arduino sketch for noise-monitor.
 */

#include "Arduino.h"
#include <CommunicationController.h>
#include <MicrophoneController.h>
#include <Message.h>
#include <MenuController.h>
#include <Sodaq_UBlox_GPS.h>
#include <LedController.h>
#include <BatteryController.h>

void setup() 
{
  toggleLED(RED);
  initLeds();  
  initCommunication();
  sodaq_gps.init(GPS_ENABLE);
  toggleLED(RED);
}


void loop() 
{
    waitForEnter();
    MenuOption mode = None;
    mode = selectModeOfOperation();
    
    if(mode == SendMessageToServer)
    {
        initADC();

        while (true) 
        {
          toggleLED(BLUE);
          char buffer[512]; //create string buffer to transmit over USB
          char timestampBuffer[64];
          NoiseMonitorMessage message = {0, 0, 0, 0, 0, 0.0}; //instantiate message with all values set to 0
          message.noiseLevel = readADC(); //read noise level from MicrophoneController    
          message.latitude = sodaq_gps.getLat();
          message.longitude = sodaq_gps.getLon();
          message.batteryVoltage = getBatteryVoltage(); 
          strncpy(timestampBuffer, sodaq_gps.getDateTimeString().c_str(), sizeof(timestampBuffer));
          strncpy(message.timestamp, timestampBuffer, 64);
          message2Char(&message, buffer); //convert message to string
          sendMessage(buffer);  //transmit string over USB    
          if (exitRequested())
          {
            break;
          }
        }
    } 
    else if (mode == SoundTestForBoard)
    {
      MenuOption submode = selectTestOperation();
      if (submode == CalibrateSpeakersInstructions)
      {
        waitForEnter();
        submode = selectTestOperation();
      }
      if (submode == BeginSoundTest )
      {
        sendMessage("Recording has begun; Play the 'sinusoid_sequence.wav' over your speakers. \n");
        unsigned long startTime = millis();
        while (true) 
        {
          toggleLED(BLUE);
          unsigned long currentTime = millis();
          unsigned long elapsedTime = currentTime - startTime;
          sendNumber(elapsedTime);
          sendMessage(",");
          sendNumber(simpleReadADC());
          sendMessage("\n");
          delay(10);
          if (exitRequested())
          {
            break;
          }
        }
      }      
    }
    else if (mode == TestBatteryMonitor)
    {
      unsigned long startTime = millis();
      while (true)
      {
        toggleLED(BLUE);
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;
        sendNumber(elapsedTime);
        sendMessage(",");
        sendNumber(getBatteryVoltage());
        sendMessage("\n");
        delay(100);
        if (exitRequested())
        {
          break;
        }
      }
    }
    
}
