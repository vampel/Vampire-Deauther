#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include <vector>
#include "config.h"

struct WiFiNetwork {
  String ssid;
  uint8_t bssid[6];
  int32_t rssi;
  uint8_t channel;
  bool is_5ghz;
};

extern std::vector<WiFiNetwork> networks;
extern bool scan_active;

void init_wifi_scan();
void perform_scan();
void start_scan();
void stop_scan();
String get_scan_results();

#endif
