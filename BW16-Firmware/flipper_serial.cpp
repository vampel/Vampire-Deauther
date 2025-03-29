#include "flipper_serial.h"
#include "wifi_scan.h"
#include "wifi_attack.h"

void init_flipper_serial() {
  // Inicialización para Flipper Zero
}

void handle_flipper_serial() {
  if(Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if(cmd == CMD_SCAN_START) {
      start_scan();
      send_to_flipper("scan_status=1");
    }
    else if(cmd == CMD_DEAUTH && current_target) {
      start_deauth(current_target);
      send_to_flipper("attack_status=1");
    }
    else if(cmd == CMD_ATTACK_STOP) {
      stop_attack();
      send_to_flipper("attack_status=0");
    }
  }
}

void send_to_flipper(const String& data) {
  Serial.println(data);
}
