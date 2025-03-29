#include "flipper_serial.h"
#include "wifi_scan.h"
#include "wifi_attack.h"

void init_flipper_serial() {
  Serial.begin(SERIAL_BAUDRATE);
}

void handle_flipper_serial() {
  if(!Serial.available()) return;
  
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  
  if(cmd == CMD_SCAN_START) {
    start_scan();
    send_to_flipper("scan:started");
  }
  else if(cmd == CMD_DEAUTH) {
    // Ejemplo: "deauth 0" (índice de red)
    int idx = cmd.substring(6).toInt();
    if(idx >= 0 && idx < networks.size()) {
      start_deauth(networks[idx].bssid, networks[idx].channel, networks[idx].is_5ghz);
    }
  }
}
