#include <Sodaq_R4X.h>
#include <Sodaq_wdt.h>
#include <Sodaq_LSM303AGR.h>

#if defined(ARDUINO_SODAQ_AUTONOMO)
/* SODAQ AUTONOMO + SODAQ NB-IoT R41XM Bee */
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin BEE_VCC
#define enablePin BEEDTR

#elif defined(ARDUINO_SODAQ_SARA)
/* SODAQ SARA AFF*/
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE

#elif defined(ARDUINO_SODAQ_SFF)
/* SODAQ SARA SFF*/
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE

#else
#error "Please use one of the listed boards or add your board."
#endif

#define DEBUG_STREAM SerialUSB
#define DEBUG_STREAM_BAUD 115200

#define STARTUP_DELAY 5000

// NL VODAFONE NB-IoT
// const char* apn = "nb.inetd.gdsp";
// const char* forceOperator = "20404"; // optional - depends on SIM / network
// const char* urat = "8";

// NL VODAFONE LTE-M
const char* apn = "live.vodafone.com";
const char* forceOperator = "20404"; // optional - depends on SIM / network
const char* urat = "7";

// NL KPN
// const char* apn = "internet.m2m";
// const char* forceOperator = "20408"; // optional - depends on SIM / network

Sodaq_R4X r4x;
Sodaq_LSM303AGR AccMeter;

static Sodaq_SARA_R4XX_OnOff saraR4xxOnOff;

void sendMessageThroughUDP()
{
    DEBUG_STREAM.println();
    DEBUG_STREAM.println("Sending message through UDP");

    int localPort = 16666;
    int socketID = r4x.socketCreate(localPort);

    if (socketID >= 7 || socketID < 0) {
        DEBUG_STREAM.println("Failed to create socket");
        return;
    }

    DEBUG_STREAM.println("Created socket!");

    String deviceId = "fPbBtWUNpUfV6NMUv4Mdyyjl";
    String token = "maker:4TtjfuCIZ9L1W1VeVnW1BCP3w2Exef11mO0EnyE";
    String value = "{\"t\":{\"value\":" + String(getBoardTemperature()) +"}}";

    String reading = deviceId + '\n' + token + '\n' + value;

    uint8_t size = reading.length();
    int lengthSent = r4x.socketSend(socketID, "37.97.216.22", 8891, (uint8_t*)reading.c_str(), size);
    DEBUG_STREAM.print("Length buffer vs sent:");
    DEBUG_STREAM.print(size);
    DEBUG_STREAM.print(",");
    DEBUG_STREAM.println(lengthSent);

    r4x.socketClose(socketID);
    DEBUG_STREAM.println();
}

void setup()
{
    sodaq_wdt_safe_delay(STARTUP_DELAY);

    Wire.begin();

    AccMeter.rebootAccelerometer();
    delay(1000);

    // Enable the Accelerometer
    AccMeter.enableAccelerometer();

    DEBUG_STREAM.begin(DEBUG_STREAM_BAUD);
    MODEM_STREAM.begin(r4x.getDefaultBaudrate());

    DEBUG_STREAM.println("Initializing and connecting... ");

    r4x.setDiag(DEBUG_STREAM);
    r4x.init(&saraR4xxOnOff, MODEM_STREAM);

    if (!r4x.connect(apn, urat)) {
       DEBUG_STREAM.println("FAILED TO CONNECT TO MODEM");
    }

    sendMessageThroughUDP();
}

/**
* Returns the board temperature.
*/
int8_t getBoardTemperature()
{
    int8_t temp = AccMeter.getTemperature();

    return temp;
}

void loop()
{
    sodaq_wdt_safe_delay(5000);
    sendMessageThroughUDP();
}
