#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <vector>
#include "config.h"

struct WiFiNetwork {
  String ssid;
  uint8_t bssid[6];
  int8_t rssi;
  uint8_t channel;
  bool is_5ghz;
};

extern std::vector<WiFiNetwork> wifi_networks;
extern uint8_t scan_status;

void init_wifi_scanner();
void perform_wifi_scan();
void start_wifi_scan();
void stop_wifi_scan();
String get_scan_results_json();

#endif
