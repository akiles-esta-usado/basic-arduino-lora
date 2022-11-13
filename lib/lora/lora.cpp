#include <Arduino.h>
#include "lora.h"
#include <capture.h>

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>



// void os_getArtEui (u1_t* buf);
// void os_getDevEui (u1_t* buf);
// void os_getDevKey (u1_t* buf);
// void onEvent (ev_t ev);
// void do_send(osjob_t* j);



// //#include <Arduino_LoRaWAN_ttn.h>

// // LoRaWAN NwkSKey, network session key
// // This is the default Semtech key, which is used by the prototype TTN
// // network initially.
// #ifdef D_NWKSKEY
// static const PROGMEM u1_t NWKSKEY[16] = D_NWKSKEY;
// #endif

// // LoRaWAN AppSKey, application session key
// // This is the default Semtech key, which is used by the prototype TTN
// // network initially.
// #ifdef D_APPSKEY
// static const u1_t PROGMEM APPSKEY[16] = D_APPSKEY;
// #endif

// // LoRaWAN end-device address (DevAddr)
// // See http://thethingsnetwork.org/wiki/AddressSpace
// #ifdef D_DEVADDR
// static const u4_t DEVADDR = D_DEVADDR;
// #endif

// // These callbacks are only used in over-the-air activation, so they are
// // left empty here (we cannot leave them out completely unless
// // DISABLE_JOIN is set in config.h, otherwise the linker will complain).
// void os_getArtEui(u1_t *buf) {}
// void os_getDevEui(u1_t *buf) {}
// void os_getDevKey(u1_t *buf) {}

// static uint8_t mydata[] = "Hello, world!";
// static osjob_t sendjob;

// // Schedule TX every this many seconds (might become longer due to duty
// // cycle limitations).
// const unsigned TX_INTERVAL = 60;

// // Pin mapping
// const lmic_pinmap lmic_pins = {
//     .nss = 10,
//     .rxtx = LMIC_UNUSED_PIN,
//     .rst = 9,
//     .dio = {2, 6, 7},
// };

// void do_send(osjob_t* j){
//     // Check if there is not a current TX/RX job running
//     if (LMIC.opmode & OP_TXRXPEND) {
//         Serial.println(F("OP_TXRXPEND, not sending"));
//     } else {
//         // Prepare upstream data transmission at the next possible time.
//         LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
//         Serial.println(F("Packet queued"));
//         Serial.println(LMIC.freq);
//     }
//     // Next TX is scheduled after TX_COMPLETE event.
// }

// void onEvent (ev_t ev) {
//     Serial.print(os_getTime());
//     Serial.print(": ");
//     switch(ev) {
//         case EV_SCAN_TIMEOUT:
//             Serial.println(F("EV_SCAN_TIMEOUT"));
//             break;
//         case EV_BEACON_FOUND:
//             Serial.println(F("EV_BEACON_FOUND"));
//             break;
//         case EV_BEACON_MISSED:
//             Serial.println(F("EV_BEACON_MISSED"));
//             break;
//         case EV_BEACON_TRACKED:
//             Serial.println(F("EV_BEACON_TRACKED"));
//             break;
//         case EV_JOINING:
//             Serial.println(F("EV_JOINING"));
//             break;
//         case EV_JOINED:
//             Serial.println(F("EV_JOINED"));
//             break;
//         case EV_RFU1:
//             Serial.println(F("EV_RFU1"));
//             break;
//         case EV_JOIN_FAILED:
//             Serial.println(F("EV_JOIN_FAILED"));
//             break;
//         case EV_REJOIN_FAILED:
//             Serial.println(F("EV_REJOIN_FAILED"));
//             break;
//             break;
//         case EV_TXCOMPLETE:
//             Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
//             if(LMIC.dataLen) {
//                 // data received in rx slot after tx
//                 Serial.print(F("Data Received: "));
//                 Serial.write(LMIC.frame+LMIC.dataBeg, LMIC.dataLen);
//                 Serial.println();
//             }
//             // Schedule next transmission
//             os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
//             break;
//         case EV_LOST_TSYNC:
//             Serial.println(F("EV_LOST_TSYNC"));
//             break;
//         case EV_RESET:
//             Serial.println(F("EV_RESET"));
//             break;
//         case EV_RXCOMPLETE:
//             // data received in ping slot
//             Serial.println(F("EV_RXCOMPLETE"));
//             break;
//         case EV_LINK_DEAD:
//             Serial.println(F("EV_LINK_DEAD"));
//             break;
//         case EV_LINK_ALIVE:
//             Serial.println(F("EV_LINK_ALIVE"));
//             break;
//          default:
//             Serial.println(F("Unknown event"));
//             break;
//     }
// }

// void LORA_init()
// {
//   Serial.println("== LORA_init begin ==");

//   // LMIC init
//   os_init();

//   // Reset the MAC state. Session and pending data transfers will be discarded.
//   LMIC_reset();

//   #ifdef PROGMEM
//     // On AVR, these values are stored in flash and only copied to RAM
//     // once. Copy them to a temporary buffer here, LMIC_setSession will
//     // copy them into a buffer of its own again.
//     uint8_t appskey[sizeof(APPSKEY)];
//     uint8_t nwkskey[sizeof(NWKSKEY)];
//     memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
//     memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
//     LMIC_setSession(0x1, DEVADDR, nwkskey, appskey);
//   #else
//     // If not running an AVR with PROGMEM, just use the arrays directly
//     LMIC_setSession(0x1, DEVADDR, NWKSKEY, APPSKEY);
//   #endif

//   // Set up the channels used by the Things Network, which corresponds
//   // to the defaults of most gateways. Without this, only three base
//   // channels from the LoRaWAN specification are used, which certainly
//   // works, so it is good for debugging, but can overload those
//   // frequencies, so be sure to configure the full frequency range of
//   // your network here (unless your network autoconfigures them).
//   // Setting up channels should happen after LMIC_setSession, as that
//   // configures the minimal channel set.
//   // LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
//   // LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
//   // LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
//   // TTN defines an additional channel at 869.525Mhz using SF9 for class B
//   // devices' ping slots. LMIC does not have an easy way to define set this
//   // frequency and support for class B is spotty and untested, so this
//   // frequency is not configured here.

//   for (int channel = 0; channel < 8; ++channel)
//   {
//     LMIC_disableChannel(channel);
//   }
//   for (int channel = 9; channel < 72; ++channel)
//   {
//     LMIC_disableChannel(channel);
//   }
//   // Disable link check validation
//   LMIC_setLinkCheckMode(0);

//   // Set data rate and transmit power (note: txpow seems to be ignored by the library)
//   LMIC_setDrTxpow(DR_SF7, 14);

//   // Start job
//   do_send(&sendjob);

//   Serial.println("== LORA_init end ==");
//   return;
// };

// void LORA_sendCapture()
// {
//   //Captura de GPS
  

//   //Envío de datos a TTN
//   Serial.println("== LORA_sendCapture begin ==");
//   // Check if there is not a current TX/RX job running
//     if (LMIC.opmode & OP_TXRXPEND) {
//         Serial.println(F("OP_TXRXPEND, not sending"));
//     } else {
//         // Prepare upstream data transmission at the next possible time.
//         LMIC_setTxData2(1, mydata, sizeof(mydata)-1, 0);
//         Serial.println(F("Packet queued"));
//         Serial.println(LMIC.freq);
//     }
//     // Next TX is scheduled after TX_COMPLETE event.
//   Serial.println("== LORA_sendCapture end ==");
//   return;
// };


void LORA_init(){ };
void LORA_sendCapture(){ };