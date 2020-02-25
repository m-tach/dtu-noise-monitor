#include "Arduino.h"
#include <ExampleController.h>

// simple example test function blinks onboard leds
void example_test_function() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  while (true)
  {
    digitalWrite(LED_BUILTIN, HIGH); // ON
    digitalWrite(LED_BLUE, HIGH); // OFF
    delay(500);
    digitalWrite(LED_BUILTIN, LOW); // OFF
    digitalWrite(LED_BLUE, LOW); // ON
    delay(500);
  }
  
}