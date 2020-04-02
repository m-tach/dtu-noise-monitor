#include <Message.h>
#include <avr/dtostrf.h>
#include "Arduino.h"
#include <Stdio.h>



static char* floatToChar(float numberToConvert)
{
    char fValue[16];
    dtostrf(numberToConvert, 3, 2, fValue);
    return fValue;
}

void message2Char(struct NoiseMonitorMessage* message, char* result)
{
    //make a buffer
    char buffer[512];

    //for each thing in the struct add :
    snprintf(buffer, sizeof(buffer), "Timestamp: %d\n", message->timestamp);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Battery Voltage: %d\n", message->batteryVoltage);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Board Temperature: %d\n", message->boardTemperature);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Lattitude: %d\n", message->latitude);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Longitude: %d\n", message->longitude);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Noise Level: %s\n", floatToChar(message->noiseLevel));
    snprintf(result, sizeof(buffer), buffer);
}


void serialize(struct NoiseMonitorMessage* message, char* result)
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