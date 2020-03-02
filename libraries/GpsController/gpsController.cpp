#include "gpsController.h"

uint8_t buffer[BUFFER_SIZE];

gpsCtlr::gpsCtlr(){
    //ENABLE GPS MODULE
    pinMode(GPS_ENABLE, OUTPUT);
    digitalWrite(GPS_ENABLE, true);

    #if (GPS_INTERFACE == WIRE_BUS)
     Wire.begin();
    #elif (GPS_INTERFACE == SERIAL_BUS)
    GPS_STREAM.begin(GPS_BAUD);
    #endif

    CONSOLE_STREAM.begin(CONSOLE_BAUD);
}

gpsCtlr::~gpsCtlr(){

}

size_t gpsCtlr::readGPS()
{
    #if (GPS_INTERFACE == WIRE_BUS)
        return readUbloxI2cStream();
    #elif (GPS_INTERFACE == SERIAL_BUS)
        return readSerialStream((Stream*) &CONSOLE_STREAM);
    #endif
}

size_t gpsCtlr::readConsole() 
{
  return readSerialStream((Stream*)&CONSOLE_STREAM);
}

#if (GPS_INTERFACE == WIRE_BUS)
size_t gpsCtlr::readUbloxI2cStream()
{
    uint16_t count = 0;
    //Require signal to Ublox
    Wire.beginTransmission(GPS_ADR);
    Wire.write((uint8_t)0XFD);
    Wire.endTransmission(false);
    Wire.requestFrom(GPS_ADR,2);
    count = (uint16_t)(Wire.read() << 8) | Wire.read();
    count = (count > BUFFER_SIZE) ? BUFFER_SIZE : count;

    if(count){
        for(size_t i=0;i < (count-1); i++){
            Wire.requestFrom(GPS_ADR,1,false);
            buffer[i] = Wire.read();
        }
        Wire.requestFrom(GPS_ADR,1);
        buffer[count-1] = Wire.read();
    }
    return count;
}
#endif

size_t gpsCtlr::readSerialStream(Stream* stream){
    uint32_t last = millis();
    size_t count = 0;
    while ((count < BUFFER_SIZE) && (millis() < (last + READ_TIMEOUT_MS)))
    {
        if (stream->available()){
            buffer[count++] = stream->read();
            last = millis();
        }
    }
    return count;
}


void gpsCtlr::writeGPS(size_t count)
{
    memset(buffer, 0, BUFFER_SIZE);
    #if (GPS_INTERFACE == WIRE_BUS)
        Wire.beginTransmission(GPS_ADR);
        Wire.write(buffer,count);
        Wire.endTransmission();
    #elif (GPS_INTERFACE == SERIAL_BUS)
        for (size_t i = 0; i < count;i++){
            GPS_STREAM.write(buffer[i]);
        }
    #endif
}

void gpsCtlr::writeConsole(size_t count)
{
    memset(buffer, 0, BUFFER_SIZE);
    for (size_t i = 0; i < count; i++){
        CONSOLE_STREAM.write(buffer[i]);
    }
}