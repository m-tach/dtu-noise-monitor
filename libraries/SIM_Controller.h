#ifndef _SIM_CONTROLLER_h
#define _SIM_CONTROLLER_h   

#include "../Sodaq_nbIOT.h"
#include "../portmap.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Checks the connection of the board to the network and establishes it if not connected. Implementation is based on the Sodaq_nbIOT library.
     * 
     *
     * @param board refers to the Sodaq_nbIOT object that should be initialized at start-up
     * @param apn refers to the name of the networks APN: internet / telenor.iot for telenor DK
     * @param cdp can be "" empty string unless otherwise provided/specified
     * @param forceOperator refers to the MCC-MNC numbers of the network. If 0, automatic mode is initiated. For telenor DK it is 23802 or 23877
     * @param band refers to the network band. 8 or 20 depending on the operator. For telenor DK it is 20.
     */
    extern void checkConnection(Sodaq_nbIOT board, char* apn, char* cdp, char* forceOperator, uint8_t band);


#endif // _COMMUNCATION_CONTROLLER_h
