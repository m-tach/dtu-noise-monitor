#define WIRE_BUS 1
#define SERIAL_BUS 2

#define GPS_INTERFACE WIRE_BUS 

#if (GPS_INTERFACE == WIRE_BUS)
  #include <Wire.h>
  #define GPS_STREAM Wire
  #define GPS_ADR 0x42
#elif (GPS_INTERFACE == SERIAL_BUS)
  #define GPS_STREAM Serial
  #define GPS_BAUD 57600
#else
  #error "Invalid GPS_INTERFACE"
#endif

#define CONSOLE_STREAM SerialUSB
#define CONSOLE_BAUD 9600

#define READ_TIMEOUT_MS 100

#define BUFFER_SIZE 256
uint8_t buffer[BUFFER_SIZE];

void setup()
{
  gpsEnable(true);

#if (GPS_INTERFACE == WIRE_BUS)
  Wire.begin();
#elif (GPS_INTERFACE == SERIAL_BUS)
  GPS_STREAM.begin(GPS_BAUD);
#endif

  CONSOLE_STREAM.begin(CONSOLE_BAUD);
}

void loop() 
{
  //Console -> GPS
  memset(buffer, 0, BUFFER_SIZE);
  writeGPS(readConsole());

  //GPS -> Console
  memset(buffer, 0, BUFFER_SIZE);
  writeConsole(readGPS());
}

void gpsEnable(bool state)
{
  //Enable GPS module
  pinMode(GPS_ENABLE, OUTPUT);
  digitalWrite(GPS_ENABLE, state);
}

size_t readGPS()
{
#if (GPS_INTERFACE == WIRE_BUS)
  return readUbloxI2cStream();
#elif (GPS_INTERFACE == SERIAL_BUS)
  return readSerialStream((Stream*)&GPS_STREAM);
#endif
}

size_t readConsole() 
{
  return readSerialStream((Stream*)&CONSOLE_STREAM);
}

#if (GPS_INTERFACE == WIRE_BUS)
size_t readUbloxI2cStream()
{
  uint16_t count = 0;
  Wire.beginTransmission(GPS_ADR);
  Wire.write((uint8_t)0xFD);
  Wire.endTransmission(false);
  Wire.requestFrom(GPS_ADR, 2);
  count = (uint16_t)(Wire.read() << 8) | Wire.read();
  count = (count > BUFFER_SIZE) ? BUFFER_SIZE : count;

  if (count) {
    for (size_t i = 0; i < (count-1); i++) {
      Wire.requestFrom(GPS_ADR, 1, false);
      buffer[i] = Wire.read();
    }
    Wire.requestFrom(GPS_ADR, 1);
    buffer[count-1] = Wire.read();
  }

  return count;
}
#endif

size_t readSerialStream(Stream* stream) 
{
  uint32_t last = millis();
  size_t count = 0;
  while ((count < BUFFER_SIZE) && (millis() < (last + READ_TIMEOUT_MS))) {
    if (stream->available()) {
      buffer[count++] = stream->read();
      last = millis();
    }
  }
  return count;  
}

void writeGPS(size_t count)
{
#if (GPS_INTERFACE == WIRE_BUS)
  Wire.beginTransmission(GPS_ADR);
  Wire.write(buffer, count);
  Wire.endTransmission();
#elif (GPS_INTERFACE == SERIAL_BUS)
  for (size_t i = 0; i < count; i++) {
    GPS_STREAM.write(buffer[i]);
  }
#endif
}

void writeConsole(size_t count)
{
  for (size_t i = 0; i < count; i++) {
    CONSOLE_STREAM.write(buffer[i]);
  }
}
