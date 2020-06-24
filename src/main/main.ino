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
long analogReadValue[32] = {};
int count = 0;
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
    float rms = 0.0;
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
          sendMessage(",");
          rms = RMSCalculation();
          sendMessage("\n");
          sendNumber(rms);
          sendMessage("\n");
          //delay(10);
          delayMicroseconds(100);
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
float RMSCalculation(void){
    int square_sum = 0;
    float rms_value = 0;
    while(count < 32){
        analogReadValue[count] = simpleReadADC();
        count++;
        //delayMicroseconds(100);
    }
  // sendNumber(count);
 //  sendMessage(",");

    // while(doneRmsFlag == 1){};
    // doneRmsFlag = 1;
    if(count == 32){
        for(int i = 0; i< 32;i++){
            square_sum = square_sum + pow(analogReadValue[i],2);
        }
        //sendNumber(square_sum);
        rms_value = sqrt(square_sum/32);
    }
    //doneRmsFlag = 0;
     count = 0;
    return rms_value;
}
