#include <Arduino.h>
#include "cs.h"
#include "capture.h"

static const uint32_t min_voltage = 200;
static const uint32_t max_voltage = 300;
static const uint32_t increment = 10;

static uint32_t actual_voltage = min_voltage;

void CS_init()
{
    Serial.println("== CS_init begin ==");
    Serial.println("== CS_init end ==");
    return;
}
void CS_capture()
{
    Serial.println("== CS_capture begin ==");

    if (max_voltage < actual_voltage)
        actual_voltage = min_voltage;

    capture.CS_charge = actual_voltage;

    actual_voltage += increment;

    Serial.println("== CS_capture end ==");
    return;
}