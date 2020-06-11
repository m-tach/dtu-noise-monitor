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
	char timestamp[64];
	uint16_t batteryVoltage;
	int8_t boardTemperature;
	double latitude;
	double longitude;
	float noiseLevel;
};

/*
 * @brief Helper function converts NoiseMonitorMessage to a char[] (serialization).
 * Intended for use with debugger (transmiting data over serial).
 * 
 * @param message struct to convert
 * @param result contains string representation of message
 */
void message2Char( struct NoiseMonitorMessage* message, char * result);

/*
 * Experimental serialization of data to binary;
 * 
 */
void serialize(struct NoiseMonitorMessage* message, char * result);

#endif // _MESSAGE_h