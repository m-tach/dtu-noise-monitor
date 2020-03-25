#include <CommunicationController.h>
#include <MicrophoneController.h>
#include "Arduino.h"

/**
 * Contains main loop for Arduino sketch for noise-monitor.
 */

void setup() 
{
  initCommunication();
  initADC();
}

void loop() 
{
  char adcReading[13] = "No reading\n";
  sendMessage("Starting reading \n");
  readADC(adcReading, 13);
  sendMessage("Finished reading \n");
  sendMessage(adcReading);
  sendMessage("\n");
}
