#ifndef _LED_CONTROLLER_h
#define _LED_CONTROLLER_h   

#include "Arduino.h"
#include <../portmap.h>

#ifdef __cplusplus
extern "C"{
#endif

enum LedColor {
    NONE = 0,
    BLUE = 1,
    RED = 2, 
    GREEN = 3
};

/**
 * @brief Initialize the LedController.
 *
 * Debugs.
 */
extern void initLeds();

/**
 * @brief Toggles an LED.
 * 
 * @param the led pin as a uint 
 */
extern void toggleLED(enum LedColor color);



#ifdef __cplusplus
} // extern "C"
#endif

#endif // _LED_CONTROLLER_h