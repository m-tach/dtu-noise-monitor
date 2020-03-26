#include "../Sodaq_nbIOT/src/Sodaq_nbIOT.h"
#include "../SIM_Controller.h"
#include "../portmap.h"

// TODO to be moved to main.ino or data.h library
//const char* apn = "internet"; // "telenor.iot" is the other option if we get test SIMs
//const char* cdp = "172.16.14.22";
//uint8_t cid = 0;
//const uint8_t band = 20;
//const char* forceOperator = "23802"; // optional - depends on SIM / network. 23802 and 23877 are for telenor DK

//Ip and port of server to send udp messages to
//const char* ip = "";
//const uint16_t port = 0;

//Initializing a sodaq_nbiot class
//Sodaq_nbIOT nbiot;


void checkConnection(board, apn, cdp, forceOperator, band){
    if (nbiot.isConnected()) {
        DEBUG_STREAM.println("Board is already connected!");
        //send message here
    } 
    else {
      DEBUG_STREAM.println("Connecting...");     
      if(nbiot.connect(apn, cdp, forceOperator, band)) {
        DEBUG_STREAM.println("Connected!");
        // send message here
      }
      else {
        DEBUG_STREAM.println("Failed to connect!");
      }
    }
}
