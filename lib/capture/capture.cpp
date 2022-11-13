#include "capture.h"
#include "Arduino.h"

capture_t capture = {
  "\0", // GPS_location
  0     // CS_charge
};


#define MSG_LEN 256
static char msg[MSG_LEN] = "\n";


void CAPTURE_printCapture()
{
  snprintf(msg, MSG_LEN, "  { %s, %d }", capture.GPS_location, capture.CS_charge);

  Serial.println(msg);
  return;
}