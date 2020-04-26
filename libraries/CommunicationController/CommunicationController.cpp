#include <CommunicationController.h>

void initCommunication()
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

void sendNumber(long message)
{
	DEBUG_STREAM.print(message);
}

int receiveMessage(void)
{
	while (DEBUG_STREAM.available()) 
	{
		return DEBUG_STREAM.read();
	}
}

