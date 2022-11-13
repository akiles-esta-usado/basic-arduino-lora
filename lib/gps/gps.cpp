#include <Arduino.h>
#include "gps.h"
#include "TinyGPS++.h"
#include "NeoSWSerial.h"


/* 
    NewSWSerial configuration
*/
NeoSWSerial nss( 4, 3);
uint16_t baudrate = 9600;


/* 
    TinyGPS++ configuration
*/
TinyGPSPlus gps;

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}




void GPS_init()
{
    Serial.println("== GPS_init begin ==");

    nss.begin(baudrate);

    Serial.println("== GPS_init end ==");
    return;
}


void GPS_capture()
{
    Serial.println("== GPS_capture begin ==");

    //for (uint32_t start = millis(); millis()- start < 5000;)
    while (1)
    {
        while (nss.available())
        {
            gps.encode(nss.read());

            if (!gps.location.isValid()) continue;
            
            Serial.print(F("Location: ")); 
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            
            
        }
    }

    
    Serial.println("== GPS_capture end ==");
    return;
}