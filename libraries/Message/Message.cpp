#include <Message.h>
#include <avr/dtostrf.h>
#include "Arduino.h"



static void floatToChar(float numberToConvert)
{
    char buffer[16];
    char fValue[16];
    dtostrf(numberToConvert, 3, 2, fValue);
    snprintf(buffer, sizeof(buffer), "%s", fValue);
}

void serialize(NoiseMonitorMessage* message, char* result)
{
    int *q = (int*)result;
    *q = message->timestamp;
    q++;
    *q = message->batteryVoltage;
    q++;
    *q = message->boardTemperature;
    q++;
    *q = message->latitude;
    q++;
    *q = message->longitude;
    q++;
    *q = message->noiseLevel;
    q++;
}