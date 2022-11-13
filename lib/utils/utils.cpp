#include "utils.h"
#include <Arduino.h>

static int _period = 200;


void UTILS_init(int period)
{
    pinMode(LED_BUILTIN, OUTPUT);
    _period = period;
}


void UTILS_blinky()
{
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(_period);                      // wait for a second
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(_period);                      // wait for a second
}