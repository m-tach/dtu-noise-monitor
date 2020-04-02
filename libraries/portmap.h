/**************
 * File contains defines, related to board configuration, as 
 * used by the libraries.
 *  
 * If a different board is to be used in the future, these 
 * mappings should be updated (without it influencing the 
 * controllers).
 */
 

#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define DEBUG_STREAM_BAUD 9600
#define STARTUP_DELAY 5000
#define ACTIVITY_DELAY 30000