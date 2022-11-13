#ifndef INCLUDE_CAPTURE_H
#define INCLUDE_CAPTURE_H


#include <stdint.h>

#define GPS_DATA_LEN 128

typedef struct _capture_t {
  char      GPS_location[GPS_DATA_LEN];
  uint32_t  CS_charge;
} capture_t;


extern capture_t capture;

void CAPTURE_printCapture();

#endif
