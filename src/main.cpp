#include <Arduino.h>
#include "utils.h"

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  blinky_init(1000);
}

// the loop function runs over and over again forever
void loop()
{
  blinky();
}
