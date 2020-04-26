#include <LedController.h>

enum LedColor currentColor = NONE;

void initLeds()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void toggleLED(enum LedColor color)
{	
	if (!(currentColor == NONE))
	{
		digitalWrite(LED_RED, HIGH);
		digitalWrite(LED_GREEN, HIGH);
		digitalWrite(LED_BLUE, HIGH);
		currentColor = NONE;
	}
	else
	{
		switch(color) {
			case RED:
				digitalWrite(LED_RED, LOW);
				digitalWrite(LED_GREEN, HIGH);
				digitalWrite(LED_BLUE, HIGH);
				break;
			case BLUE:
				digitalWrite(LED_RED, HIGH);
				digitalWrite(LED_GREEN, HIGH);
				digitalWrite(LED_BLUE, LOW);
				break;
			case GREEN:
				digitalWrite(LED_RED, HIGH);
				digitalWrite(LED_GREEN, LOW);
				digitalWrite(LED_BLUE, HIGH);
				break;
		}
		currentColor = color;
	}
}

