#include <Arduino.h>
#include "cs.h"
#include "capture.h"


void CS_init()
{
    Serial.println("== CS_init begin ==");
    Serial.println("== CS_init end ==");
    return;
}
void CS_capture()
{
    Serial.println("== CS_capture begin ==");
    capture.CS_charge += 1;
    Serial.println("== CS_capture end ==");
    return;
}