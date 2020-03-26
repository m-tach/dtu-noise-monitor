#ifndef _MESSAGE_h
#define _MESSAGE_h   

#include <Stdint.h>
/**
 * @file Contains the shared Message structure for communication between
 * 		 boards and the server.
 */

/*
 * @brief Data packet for communication.
 * //TODO: add to readme; explain each field;
 */
struct NoiseMonitorMessage
{
	uint32_t timestamp;
	uint8_t batteryVoltage;
	int8_t boardTemperature;
	uint32_t latitude;
	uint32_t longitude;
	float noiseLevel;
};

/*
 * @brief Helper function converts NoiseMonitorMessage to a char[] (serialization).
 * Intended for use with debugger (transmiting data over serial).
 * 
 * @param message struct to convert
 * @param result contains string representation of message
 */
void serialize( NoiseMonitorMessage* message, char * result);

#endif // _MESSAGE_h