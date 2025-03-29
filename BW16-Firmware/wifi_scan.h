#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include <WiFi.h>
#include <vector>

struct WiFiNetwork {
  String ssid;
  uint8_t bssid[6];
  int8_t rssi;
  uint8_t channel;
  bool is_5ghz;
};

extern std::vector<WiFiNetwork> networks;
extern bool scan_active;

void init_wifi_scan();
void perform_wifi_scan();
void start_scan();
void stop_scan();

#endif
