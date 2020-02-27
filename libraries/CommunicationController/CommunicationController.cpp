#include <CommunicationController.h>

void initUSBDriver()
{
	pinMode(powerPin, OUTPUT);
	digitalWrite(powerPin, HIGH);
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
	DEBUG_STREAM.begin(9600);

}

void sendMessage(char * message)
{
	DEBUG_STREAM.write(message);
}