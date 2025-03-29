#include "wifi_scan.h"
#include <WiFi.h>

std::vector<WiFiNetwork> networks;
bool scan_active = false;

void init_wifi_scan() {
  networks.reserve(MAX_NETWORKS);
}

void set_channel(uint8_t channel) {
  String cmd = "iwpriv wlan0 set_channel ";
  cmd += channel;
  system(cmd.c_str());
  delay(5);
}

void perform_scan() {
  static uint8_t current_channel = 0;
  static bool scanning_5ghz = false;
  
  if(!scanning_5ghz) {
    set_channel(CHANNELS_2GHZ[current_channel]);
    scan_channel(CHANNELS_2GHZ[current_channel], false);
    current_channel = (current_channel + 1) % sizeof(CHANNELS_2GHZ);
    if(current_channel == 0) scanning_5ghz = true;
  } else {
    set_channel(CHANNELS_5GHZ[current_channel]);
    scan_channel(CHANNELS_5GHZ[current_channel], true);
    current_channel = (current_channel + 1) % sizeof(CHANNELS_5GHZ);
    if(current_channel == 0) scanning_5ghz = false;
  }
}

void scan_channel(uint8_t channel, bool is_5ghz) {
  int n = WiFi.scanNetworks(false, true);
  
  for(int i = 0; i < n && networks.size() < MAX_NETWORKS; i++) {
    WiFiNetwork net;
    net.ssid = WiFi.SSID(i);
    WiFi.BSSID(i, net.bssid);
    net.rssi = WiFi.RSSI(i);
    net.channel = channel;
    net.is_5ghz = is_5ghz;
    
    bool duplicate = false;
    for(const auto& n : networks) {
      if(memcmp(n.bssid, net.bssid, 6) == 0) {
        duplicate = true;
        break;
      }
    }
    
    if(!duplicate) {
      networks.push_back(net);
    }
  }
}
