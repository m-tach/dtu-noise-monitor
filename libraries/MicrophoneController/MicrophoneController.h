#ifndef _MICROPHONE_CONTROLLER_h
#define _MICROPHONE_CONTROLLER_h   



#include <Sodaq_R4X.h>
#include <Sodaq_wdt.h>
#include <string.h>

void initADC(void); 
void readADC(char *a, size_t asize);


#endif // _MICROPHONE_CONTROLLER_h