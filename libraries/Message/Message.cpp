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
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Board Temperature: %u\n", message->boardTemperature);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Lattitude: %f\n", message->latitude);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Longitude: %f\n", message->longitude);
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "Noise Level: %s\n", floatToChar(message->noiseLevel));
    snprintf(result, sizeof(buffer), buffer);
}
