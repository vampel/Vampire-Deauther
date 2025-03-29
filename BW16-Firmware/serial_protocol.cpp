// serial_protocol.cpp
#include "serial_protocol.h"
#include "wifi_scan.h"
#include "wifi_attack.h"
#include "config.h"

void init_serial_protocol() {
    // Inicialización si es necesaria
}

void handle_serial_commands() {
    if(Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        if(command == CMD_SCAN_START) {
            start_scan();
            Serial.println("SCAN_STARTED");
        } else if(command == CMD_SCAN_STOP) {
            stop_scan();
            Serial.println("SCAN_STOPPED");
        } else if(command.startsWith(CMD_SELECT_TARGET)) {
            // Procesar selección de objetivo
            int index = command.substring(strlen(CMD_SELECT_TARGET)).toInt();
            if(index >= 0 && index < networks.size()) {
                selected_target = &networks[index];
                Serial.println("TARGET_SELECTED");
            }
        } else if(command == CMD_ATTACK_DEAUTH) {
            if(selected_target) {
                start_deauth(selected_target);
                Serial.println("ATTACK_STARTED");
            }
        } else if(command == CMD_ATTACK_STOP) {
            stop_attack();
            Serial.println("ATTACK_STOPPED");
        }
    }
}

void send_scan_results() {
    if(!scan_active) return;
    
    Serial.println("SCAN_RESULTS_START");
    for(const auto& net : networks) {
        Serial.print(net.ssid);
        Serial.print(",");
        Serial.print(net.channel);
        Serial.print(",");
        Serial.print(net.rssi);
        Serial.print(",");
        Serial.print(net.is_5ghz ? "5GHz" : "2.4GHz");
        Serial.println();
    }
    Serial.println("SCAN_RESULTS_END");
}
