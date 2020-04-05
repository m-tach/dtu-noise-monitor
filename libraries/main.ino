#include <Arduino.h>
#include <Sodaq_UBlox_GPS.h>

#define MySerial SERIAL_PORT_MONITOR

void setup() {
  // put your setup code here, to run once:
  while(!SerialUSB){}
  MySerial.begin(57600);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);
  pinMode(LED_BLUE, OUTPUT);

  do_flash_led(LED_RED);
  do_flash_led(LED_GREEN);
  do_flash_led(LED_BLUE);
  MySerial.println("SODAQ LoRaONE test_gps is starting ...");

  sodaq_gps.init(GPS_ENABLE);
 // sodaq_gps.setDiag(MySerial);
}
void do_flash_led(int pin)
{
    for (size_t i = 0; i < 2; ++i) {
        delay(100);
        digitalWrite(pin, LOW);
        delay(100);
        digitalWrite(pin, HIGH);
    }
}
void loop() {
  // put your main code here, to run repeatedly:
   MySerial.println("waiting in loop() ...");
    // Try to get a GPS scan and when we get a fix we print our location. We are
    // passing true to keep the GPS enabled after a scan
    MySerial.println(String(" datetime = ") + sodaq_gps.getDateTimeString());
    if (sodaq_gps.scan(true))
    {
      MySerial.print("We are at latitude ");
      MySerial.print(sodaq_gps.getLat(), 13);
      MySerial.print(" longitude ");
      MySerial.print(sodaq_gps.getLon(), 13);
      MySerial.println(String(" datetime = ") + sodaq_gps.getDateTimeString());
    }
    delay(1000);
}
