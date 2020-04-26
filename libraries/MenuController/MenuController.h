#ifndef _MENU_CONTROLLER_h
#define _MENU_CONTROLLER_h   

#include "Arduino.h"
#include <../portmap.h>
#include <CommunicationController.h>
#include <LedController.h>

#ifdef __cplusplus
extern "C"{
#endif

enum MenuOption {
    None = 0, 
    SendMessageToServer = 1,
    SoundTestForBoard = 2,
    CalibrateSpeakersInstructions = 3, 
    BeginSoundTest = 4
};

enum MenuOption selectModeOfOperation();
enum MenuOption selectTestOperation();
void waitForEnter(void);
bool exitRequested(void);




#ifdef __cplusplus
} // extern "C"
#endif

#endif // _COMMUNCATION_CONTROLLER_h