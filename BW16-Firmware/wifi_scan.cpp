#include "wifi_scan.h"
#include "config.h"

std::vector<WiFiNetwork> networks;
bool scan_active = false;

const uint8_t channels_2ghz[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const uint8_t channels_5ghz[] = {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 
                                112, 116, 120, 124, 128, 132, 136, 140, 144, 
                                149, 153, 157, 161, 165};

void init_wifi_scan() {
  networks.reserve(MAX_SCAN_NETWORKS);
}

void set_wifi_channel(uint8_t channel) {
  String cmd = "iwpriv wlan0 set_channel ";
  cmd += channel;
  system(cmd.c_str());
}

void perform_wifi_scan() {
  static uint8_t current_channel = 0;
  static bool scanning_5ghz = false;
  
  if(!scanning_5ghz && current_channel < sizeof(channels_2ghz)) {
    set_wifi_channel(channels_2ghz[current_channel]);
    scan_current_channel(channels_2ghz[current_channel]);
    current_channel++;
  } else if(!scanning_5ghz) {
    scanning_5ghz = true;
    current_channel = 0;
  }
  
  if(scanning_5ghz && current_channel < sizeof(channels_5ghz)) {
    set_wifi_channel(channels_5ghz[current_channel]);
    scan_current_channel(channels_5ghz[current_channel]);
    current_channel++;
  } else if(scanning_5ghz) {
    scanning_5ghz = false;
    current_channel = 0;
  }
}

void scan_current_channel(uint8_t channel) {
  int16_t n = WiFi.scanNetworks();
  
  for(int16_t i = 0; i < n && networks.size() < MAX_SCAN_NETWORKS; i++) {
    WiFiNetwork network;
    network.ssid = WiFi.SSID(i);
    
    uint8_t bssid[6];
    if(WiFi.BSSID(i, bssid)) {
      memcpy(network.bssid, bssid, 6);
      network.rssi = WiFi.RSSI(i);
      network.channel = channel;
      network.is_5ghz = (channel >= 36);
      
      bool duplicate = false;
      for(const auto& net : networks) {
        if(memcmp(net.bssid, network.bssid, 6) == 0) {
          duplicate = true;
          break;
        }
      }
      
      if(!duplicate) {
        networks.push_back(network);
      }
    }
  }
  
  delay(CHANNEL_HOP_INTERVAL);
}

void start_scan() {
  scan_active = true;
  networks.clear();
}

void stop_scan() {
  scan_active = false;
}
