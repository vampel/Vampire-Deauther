#include "wifi_scanner.h"
#include <WiFi.h>

std::vector<WiFiNetwork> wifi_networks;
uint8_t scan_status = SCAN_INACTIVE;

void init_wifi_scanner() {
  wifi_networks.reserve(MAX_NETWORKS);
}

void set_wifi_channel(uint8_t channel) {
  String cmd = "iwpriv wlan0 set_channel ";
  cmd += channel;
  system(cmd.c_str());
  delay(15);
}

void perform_wifi_scan() {
  static uint8_t current_band = 0; // 0:2.4GHz, 1:5GHz
  static uint8_t channel_index = 0;
  
  if(current_band == 0) {
    if(channel_index < sizeof(CHANNELS_2GHZ)) {
      set_wifi_channel(CHANNELS_2GHZ[channel_index]);
      scan_current_channel(CHANNELS_2GHZ[channel_index], false);
      channel_index++;
    } else {
      current_band = 1;
      channel_index = 0;
    }
  } else {
    if(channel_index < sizeof(CHANNELS_5GHZ)) {
      set_wifi_channel(CHANNELS_5GHZ[channel_index]);
      scan_current_channel(CHANNELS_5GHZ[channel_index], true);
      channel_index++;
    } else {
      current_band = 0;
      channel_index = 0;
    }
  }
}

void scan_current_channel(uint8_t channel, bool is_5ghz) {
  int16_t num_networks = WiFi.scanNetworks();
  
  for(int i = 0; i < num_networks && wifi_networks.size() < MAX_NETWORKS; i++) {
    WiFiNetwork network;
    network.ssid = WiFi.SSID(i);
    
    uint8_t bssid[6];
    if(WiFi.BSSID(i, bssid)) {
      memcpy(network.bssid, bssid, 6);
      network.rssi = WiFi.RSSI(i);
      network.channel = channel;
      network.is_5ghz = is_5ghz;
      
      bool exists = false;
      for(const auto& net : wifi_networks) {
        if(memcmp(net.bssid, network.bssid, 6) == 0) {
          exists = true;
          break;
        }
      }
      
      if(!exists) {
        wifi_networks.push_back(network);
      }
    }
  }
}

String get_scan_results_json() {
  String json = "[";
  for(size_t i = 0; i < wifi_networks.size(); i++) {
    if(i != 0) json += ",";
    json += "{";
    json += "\"ssid\":\"" + wifi_networks[i].ssid + "\",";
    json += "\"bssid\":\"" + format_bssid(wifi_networks[i].bssid) + "\",";
    json += "\"channel\":" + String(wifi_networks[i].channel) + ",";
    json += "\"rssi\":" + String(wifi_networks[i].rssi) + ",";
    json += "\"band\":\"" + (wifi_networks[i].is_5ghz ? "5GHz" : "2.4GHz") + "\"";
    json += "}";
  }
  json += "]";
  return json;
}

String format_bssid(const uint8_t* bssid) {
  char buf[18];
  snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
           bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
  return String(buf);
}
