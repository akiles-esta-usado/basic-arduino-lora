#include <Arduino.h>
#include "capture.h"
#include "utils.h"
#include "gps.h"
#include "cs.h"
#include "lora.h"


void setup()
{
  Serial.begin(9600);

  UTILS_init(100);
  GPS_init();
  CS_init();
  LORA_init();
}

// the loop function runs over and over again forever
void loop()
{
   // Indicator of new capture
  UTILS_blinky();

  // Charging Station and GPS data capture
  CS_capture(); 
  GPS_capture();

  // Debug: Print capture
  CAPTURE_printCapture();


  // Sending to internets
  LORA_sendCapture();


  delay(2000); // awaiting bewteen captures
  Serial.println("");
}
