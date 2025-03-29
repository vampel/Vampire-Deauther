#include "flipper_serial.h"

void init_flipper_serial() {
  // Inicialización adicional si es necesaria
}

void handle_flipper_commands() {
  if(Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if(command == CMD_SCAN_START) {
      start_wifi_scan();
      Serial.println("[+] Scan started");
    } 
    else if(command == CMD_SCAN_STOP) {
      stop_wifi_scan();
      Serial.println("[+] Scan stopped");
    }
    else if(command.startsWith("TARGET ")) {
      int target_id = command.substring(7).toInt();
      if(target_id >= 0 && target_id < wifi_networks.size()) {
        current_target = &wifi_networks[target_id];
        Serial.println("[+] Target set: " + current_target->ssid);
      }
    }
    else if(command == CMD_ATTACK_DEAUTH && current_target) {
      start_deauth_attack(current_target);
    }
    else if(command == CMD_ATTACK_BEACON) {
      start_beacon_spam();
    }
    else if(command == CMD_ATTACK_STOP) {
      stop_all_attacks();
    }
    else if(command == "GET_SCAN") {
      Serial.println(get_scan_results_json());
    }
  }
}

void send_to_flipper(const String& message) {
  Serial.println(message);
}
