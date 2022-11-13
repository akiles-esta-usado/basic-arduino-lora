#include <Arduino.h>
#include "gps.h"
#include "TinyGPS++.h"
#include "NeoSWSerial.h"
#include "capture.h"

#define MAX_TIMEOUT 100000

/*
    NewSWSerial configuration
*/
NeoSWSerial nss(4, 3);
uint16_t baudrate = 9600;

/*
    TinyGPS++ configuration
*/
#define FLOAT_SIZE 64

TinyGPSPlus gps;
char LAT[FLOAT_SIZE] = "\0";
char LNG[FLOAT_SIZE] = "\0";


void displayInfo()
{
  Serial.print(F("Location: "));

  if (!gps.location.isValid())
    Serial.print(F("INVALID"));
  else
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }

  Serial.print(F("  Date/Time: "));

  if (!gps.date.isValid())
    Serial.print(F("INVALID"));
  else
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }

  Serial.print(F(" "));
  if (!gps.time.isValid())
    Serial.print(F("INVALID"));
  else
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }

  Serial.println();
}

void updateLocation()
{
  if (!gps.location.isValid())
    return;

  dtostrf(gps.location.lat(),10, 6, LAT);
  dtostrf(gps.location.lng(),10, 6, LNG);

  snprintf(
      capture.GPS_location, GPS_DATA_LEN, "%s,%s",
      LAT,
      LNG);

  Serial.print("Location updated: ");
  Serial.println(capture.GPS_location);
}

void GPS_fakeInit()
{
  const char *gpsStream =
      "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
      "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
      "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
      "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
      "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
      "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

  // With fake data, we only have one sample
  while (!gps.location.isValid())
  {
    gps.encode(*gpsStream++);
  };

  displayInfo();
}

void GPS_fakeCapture()
{
  // Already with one valid sample.
  updateLocation();
}

void GPS_realInit()
{
  uint32_t end = MAX_TIMEOUT + millis();

  while (1)
  {
    if (end - millis() < 0)
    {
      Serial.println("There is no GPS data");
      break;
    }

    while (nss.available())
    {
      gps.encode(nss.read());
      if (gps.location.isValid())
      {
        break;
      }
    }
  }
}

void GPS_realCapture()
{
  uint32_t end = MAX_TIMEOUT + millis();
  bool locationIsUpdatable = false;

  // for (uint32_t start = millis(); millis()- start < 5000;)
  while (!locationIsUpdatable)
  {
    if (end - millis() < 0)
    {
      Serial.println("No GPS update");
      break;
    }

    while (nss.available())
    {
      gps.encode(nss.read());

      if (!gps.location.isUpdated())
      {
        locationIsUpdatable = true;
        continue;
      }

      break;
    }
  }

  updateLocation();
}

void GPS_init()
{
  Serial.println("== GPS_init begin ==");

  nss.begin(baudrate);

  GPS_fakeInit();

  Serial.println("== GPS_init end ==");
  return;
}

void GPS_capture()
{
  Serial.println("== GPS_capture begin ==");

  GPS_fakeCapture();

  Serial.println("== GPS_capture end ==");
  return;
}