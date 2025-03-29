#pragma once
#include <WiFi.h>
#include <BLEDevice.h>

void handleCommand(String cmd) {
  if (cmd.startsWith("SCAN_2.4")) {
    scanNetworks(WIFI_BAND_2_4GHZ);
  } else if (cmd.startsWith("SCAN_5")) {
    scanNetworks(WIFI_BAND_5GHZ);
  } else if (cmd.startsWith("DEAUTH")) {
    String mac = cmd.substring(7);
    deauthDevice(mac.c_str());
  } else if (cmd == "BLE_SPAM") {
    startBleSpam();
  }
}

void scanNetworks(wifi_band_t band) {
  WiFi.scanNetworks(false, true, false, 100, 0, "", band);
  for (int i = 0; i < WiFi.scanComplete(); i++) {
    Serial.printf("%s|%s|%d\n", WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str(), WiFi.channel(i));
  }
}

void deauthDevice(const char* mac) {
  // Implementar usando esp_wifi_80211_tx() (requiere SDK Realtek)
}

void startBleSpam() {
  BLEServer* server = BLEDevice::createServer();
  BLEAdvertising* adv = server->getAdvertising();
  adv->start();
}
