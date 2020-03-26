#include <Sodaq_UBlox_GPS.h>
#include <Sodaq_R4X.h>
#include <Sodaq_wdt.h>
#include <string.h>

//#if defined(ARDUINO_SODAQ_AUTONOMO)
///* SODAQ AUTONOMO + SODAQ NB-IoT R41XM Bee */
//#define DEBUG_STREAM SerialUSB
//#define MODEM_STREAM Serial1
//#define powerPin BEE_VCC
//#define enablePin BEEDTR
//
//#elif defined(ARDUINO_SODAQ_SARA)
/* SODAQ SARA AFF*/
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE

//#elif defined(ARDUINO_SODAQ_SFF)
///* SODAQ SARA SFF*/
//#define DEBUG_STREAM SerialUSB
//#define MODEM_STREAM Serial1
//#define powerPin SARA_ENABLE
//#define enablePin SARA_TX_ENABLE
//
//#else
//#error "Please use one of the listed boards or add your board."
//#endif

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

#define STARTUP_DELAY 5000

// NL VODAFONE NB-IoT
const char* apn = "nb.inetd.gdsp";
const char* forceOperator = "22210"; // optional - depends on SIM / network
const char* urat = "8";

Sodaq_R4X r4x;
//Sodaq_LSM303AGR AccMeter;

static Sodaq_SARA_R4XX_OnOff saraR4xxOnOff;

#include "SOS_A_float.h"
#include "SV_A_float.h"

#define NS 20000

void sendMessageThroughUDP(String value) {

  DEBUG_STREAM.println();
  DEBUG_STREAM.println("Sending message through UDP");

  int localPort = 16666;
  int socketID = r4x.socketCreate(localPort);

  DEBUG_STREAM.print("socketID = ");
  DEBUG_STREAM.println(socketID);

  if (socketID >= 7 || socketID < 0) {
    DEBUG_STREAM.println("Failed to create socket");
    return;
  }

  DEBUG_STREAM.println("Created socket!");

  String deviceId = "VfbTrH3ejfA78Io9bHBGk5rO";
  String token = "vodafone:4HLg85WInLyVG0lqFxJlq4FR97OnLLZyazetNd41";
  String reading = deviceId + '\n' + token + '\n' + value;

  uint8_t size = reading.length();
  r4x.socketSend(socketID, "40.68.172.187", 8891, (uint8_t*)reading.c_str(), size);
  r4x.socketClose(socketID);
}

void setup() {

  sodaq_wdt_safe_delay(STARTUP_DELAY);

  SerialUSB.begin(115200);
  while (!SerialUSB) {}
  SerialUSB.println("press enter...");
  while (!SerialUSB.available());

  initADC();

  MODEM_STREAM.begin(r4x.getDefaultBaudrate());

  DEBUG_STREAM.println("Initializing and connecting... ");

  r4x.setDiag(DEBUG_STREAM);
  //r4x.init(&saraR4xxOnOff, MODEM_STREAM);
  //r4x.connect(apn, urat);

  //if (!r4x.connect(apn, urat)) {
  //  DEBUG_STREAM.println("FAILED TO CONNECT TO MODEM");
  //}

  initSleep();
}

void loop() {
  int i = 0;

  float input;

  float y1 = 0;
  float y2 = 0;
  float y3 = 0;
  float buf11 = 0.0;
  float buf21 = 0.0;
  float buf12 = 0.0;
  float buf22 = 0.0;
  float buf13 = 0.0;
  float buf23 = 0.0;

  float squarer;
  
  float pr2 = 20e-6 * 20e-6;

  float Leq;

  float sum = 0;

  float lat;
  float lon;

  char a[13];
  String value;


  sodaq_wdt_reset();                  // restting the watchdog
  sodaq_wdt_disable();

  sodaq_gps.init(GPS_ENABLE);
  SerialUSB.println("waiting in loop() ...");
  if (sodaq_gps.scan(true))
  {
    SerialUSB.print("We are at latitude ");
    lat = sodaq_gps.getLat();
    lon = sodaq_gps.getLon();
    SerialUSB.print(lat, 13);
    SerialUSB.print(" longitude ");
    SerialUSB.println(lon, 13);
  } else {
    SerialUSB.println("NO SCAN!");
  }
  digitalWrite(GPS_ENABLE, HIGH);

  for (i = 0; i < NS; i++) {
    ADC->CTRLA.bit.ENABLE = 0x01;
    syncADC();
    ADC->SWTRIG.bit.START = 1;
    while (ADC->INTFLAG.bit.RESRDY == 0);
    syncADC();
    ADC->CTRLA.bit.ENABLE = 0;
    syncADC();

    input = (float)(ADC->RESULT.reg) / 4095;

    y1 = SV_A[0] * SOS_A[0][0] * input + buf11;
    buf11 = SV_A[0] * SOS_A[0][1] * input - SOS_A[0][4] * y1 + buf21;
    buf21 = SV_A[0] * SOS_A[0][2] * input - SOS_A[0][5] * y1;

    y2 = SOS_A[1][0] * y1 + buf12;
    buf12 = SOS_A[1][1] * y1 - SOS_A[1][4] * y2 + buf22;
    buf22 = SOS_A[1][2] * y1 - SOS_A[1][5] * y2;

    y3 = SOS_A[2][0] * y2 + buf13;
    buf13 = SOS_A[2][1] * y2 - SOS_A[2][4] * y3 + buf23;
    buf23 = SOS_A[2][2] * y2 - SOS_A[2][5] * y3;

    squarer = y3 * y3;

    sum += squarer;

  }

  Leq = 10 * log10((sum / NS) / pr2);
  SerialUSB.println(Leq);

  memcpy(&a[0], &Leq, sizeof(Leq));  
  memcpy(&a[4], &lat, sizeof(lat));
  memcpy(&a[8], &lon, sizeof(lon));
  a[12] = 0;
  value = String(a);

  sendMessageThroughUDP(value);


  y1 = 0.0;
  y2 = 0.0;
  y3 = 0.0;

  buf11 = 0.0;
  buf21 = 0.0;
  buf12 = 0.0;
  buf22 = 0.0;
  buf13 = 0.0;
  buf23 = 0.0;

  sum = 0;

  sodaq_wdt_enable(WDT_PERIOD_8X);    // watchdog expires in ~8 seconds
  systemSleep();
}

static __inline__ void syncADC() __attribute__((always_inline, unused));
static void syncADC() {
  while (ADC->STATUS.bit.SYNCBUSY == 1);
}

void initADC() {
  SYSCTRL->OSC8M.bit.PRESC = 0;                          // no prescaler (is 8 on reset)
  SYSCTRL->OSC8M.reg |= 1 << SYSCTRL_OSC8M_ENABLE_Pos;   // enable source

  REG_PORT_DIRCLR1 = PORT_PA11;
  PORT->Group[0].PINCFG[11].bit.PMUXEN = 1;
  PORT->Group[0].PMUX[5].reg = PORT_PMUX_PMUXO_B;

  GCLK->GENDIV.bit.ID = 0x03;
  GCLK->GENDIV.bit.DIV = 9;
  GCLK->GENCTRL.reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_ID(3); // GCLK_GENCTRL_DIVSEL don't need this, it makes divide based on power of two
  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ) {}

  PM->APBCSEL.bit.APBCDIV = 0;                           // no prescaler
  REG_PM_APBCMASK |= PM_APBCMASK_ADC;

  GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(3) | GCLK_CLKCTRL_ID(30);
  while (GCLK->STATUS.bit.SYNCBUSY == 1);

  REG_ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC0; //set vref for ADC to VCC
  syncADC();
  // Sampling time, no extra sampling half clock-cycles
  REG_ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(0);
  //
  // Input control and input scan
  REG_ADC_INPUTCTRL |= ADC_INPUTCTRL_GAIN_1X |
                       ADC_INPUTCTRL_MUXNEG_GND |
                       ADC_INPUTCTRL_MUXPOS_PIN19;

  ADC->CTRLB.bit.RESSEL = 0;
  syncADC();
  ADC->CTRLB.bit.PRESCALER = 0x0; //DIV4
  syncADC();
  ADC->CTRLA.bit.ENABLE = 0x01;
  syncADC();
  ADC->CTRLA.bit.ENABLE = 0;
  syncADC();
}

void initSleep()
{
  // Set the sleep mode
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/**
   Powers down all devices and puts the system to deep sleep.
*/
void systemSleep()
{

  __WFI(); // SAMD sleep

}
