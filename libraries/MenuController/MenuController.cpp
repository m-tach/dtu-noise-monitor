#include <MenuController.h>




int waitForUser(void)
{	

	while (true)
	{
		int messageReceived = receiveMessage();
		if (messageReceived == 49)
		{
			return 1;		
		} else if (messageReceived == 50){
			return 2;
		} else if (messageReceived == 51){
			return 3;
		}
	}
    
}


enum MenuOption selectTestOperation()
{	    
    sendMessage("To do the test, you need the following: \n");
    sendMessage(" - laptop with calibrated speaker \n"); 
    sendMessage(" - phone with phonometer application \n"); 
    sendMessage(" - file with sample tone \n"); 
	sendMessage("==============================================\n");
    sendMessage("Please select test operation:\n"); 
    sendMessage("   1: Help me calibrate my speakers \n");
    sendMessage("   2: Begin sound test \n");
	
	toggleLED(RED);
	int result = waitForUser();
	sendMessage("==============================================\n");
	toggleLED(RED);
	
	switch (result)
	{
		case 1:
			sendMessage("Selected: Help me calibrate my speakers.\n");
			sendMessage("==============================================\n");
			sendMessage("Instructions on how to calibrate: \n");
            sendMessage("   1. Install a Sound Level Meter App on your phone.\n");
            sendMessage("   2. Put phone close to the computer speaker so app measures sound in dB.\n");
            sendMessage("   3. Play '200.wav' over speakers. Adjust laptop volume so you read 58.8 dB on the phone app.\n");
			sendMessage("   4. Adjust laptop volume so you read 58.8 dB on the phone app.\n");
			sendMessage("==============================================\n");
			return CalibrateSpeakersInstructions;
		case 2:
			sendMessage("Selected: Begin sound test.\n"); 
			sendMessage("==============================================\n");
			return BeginSoundTest;
	}
}

void waitForEnter(void)
{
	while (true)
	{
		int messageReceived = receiveMessage();
		if (messageReceived == 10)
		{
			return;
		}
	}
}

bool exitRequested(void)
{
	while (true)
	{
		int messageReceived = receiveMessage();
		if (messageReceived == 81)
		{
			sendMessage("==============================================\n");
			sendMessage("Exit requested by user\n");
			sendMessage("==============================================\n");

			return true;
		}
		return false;
	}
}

enum MenuOption selectModeOfOperation()
{
	int choice = 0;

	sendMessage("Please select mode of operation: \n");
	sendMessage("   1: Send message to server \n");
	sendMessage("   2: Sound test for board \n");
	sendMessage("   3: Test battery monitor \n");
	toggleLED(RED);
	int result = waitForUser();
	sendMessage("==============================================\n");
	toggleLED(RED);
	switch (result)
	{
		case 1:
			sendMessage("Mode selected: Send message to server\n");
			sendMessage("==============================================\n");
			return SendMessageToServer;
		case 2:
			sendMessage("Mode selected: Sound test for board\n"); 
			sendMessage("==============================================\n");
			return SoundTestForBoard;
		case 3:
			sendMessage("Mode selected: test battery monitor\n");
			sendMessage("==============================================\n");
			return TestBatteryMonitor;
	}

}

enum MenuOption testBatteryMonitor()
{
	int choice = 0;

	
}