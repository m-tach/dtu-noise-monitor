#ifndef _COMMUNCATION_CONTROLLER_h
#define _COMMUNCATION_CONTROLLER_h   

#include "Arduino.h"
#include <portmap.h>

/**
 * @brief Transmit/receive data. 
 *
 * Current implementation uses USB.
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initialize the CommunicationController.
 *
 * Current implementation uses USB.
 */
extern void initCommunication();

/**
 * @brief Sends a string to the current serial port.
 * 
 * Current implementation uses USB.
 *
 * @param the message as a string 
 */
extern void sendMessage(char * message);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _COMMUNCATION_CONTROLLER_h