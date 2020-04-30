/**
 * @note The logic in this controller has been ported from the sketch, available in examples/CARAUDIRE. 
 * It is still a work in progress - a lot needs to be cleared out.
 * 
 */

#ifndef _MICROPHONE_CONTROLLER_h
#define _MICROPHONE_CONTROLLER_h   


#include <Sodaq_R4X.h>
#include <Sodaq_wdt.h>
#include <string.h>

/**
 * @brief Initiate the ADC on the board. 
 * NOT VERIFIED
 * 
 */
void initADC(void); 

/**
 * @brief Reads the ADC value from the board. 
 * NOT VERIFIED
 * 
 * @return a float representing the noise level.
 */
float readADC(void);

/**
 * @brief Put the system to sleep for 8 seconds (watchdog triggered reset). 
 * 
 * Powers down all devices.
 */
void systemSleep(void);

/**
 * Averages 32 samples.
 */ 
long averageReadADC(void);

/**
 * Returns a single sample.
 */ 
long simpleReadADC(void);

#endif // _MICROPHONE_CONTROLLER_h