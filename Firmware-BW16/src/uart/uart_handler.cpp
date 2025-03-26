#include "uart_handler.h"
#include "WiFiDeauth.h"  // Para ejecutar comandos
#include "mac_parser.h"

void UARTHandler::parse_command(const String& cmd) {
    if (cmd.startsWith("DEAUTH24 ")) {
        uint8_t mac[6];
        if (MACParser::parse(cmd.substring(9), mac)) {
            WiFiDeauth::attack(false, mac);
            send_response("[OK] Deauth 2.4GHz iniciado");
        } else {
            send_response("[ERROR] MAC inválida");
        }

void UARTHandler::init(uint32_t baud_rate) {
    Serial.begin(baud_rate);
    while (!Serial); // Espera conexión
}

void UARTHandler::read_commands() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        parse_command(cmd);
    }
}

void UARTHandler::parse_command(const String& cmd) {
    if (cmd.startsWith("DEAUTH24 ")) {
        String mac_str = cmd.substring(9);
        uint8_t mac[6];
        if (sscanf(mac_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
                   &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
            WiFiDeauth::attack(false, mac);
        }
    }
    
}

void UARTHandler::send_response(const String& message) {
    Serial.println(message);
}

void UARTHandler::parse_command(const String& cmd) {
    if (cmd.length() == 0) return;

    if (cmd.startsWith("DEAUTH24 ")) {
        uint8_t mac[6];
        if (MACParser::parse(cmd.substring(9), mac)) {
            if (WiFiDeauth::attack(false, mac)) {
                send_response("[OK] 2.4GHz attack started");
            } else {
                send_response("[ERROR] WiFi init failed");
            }
        } else {
            send_response("[ERROR] Invalid MAC format");
        }
    }
    
}

bool verify_checksum(const String& cmd) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < cmd.length() - 3; i++) { // Ej: "CMD...:XX"
        checksum ^= cmd[i];
    }
    return cmd.substring(cmd.length() - 2) == String(checksum, HEX);
}

void parse_command(const String& cmd) {
    if (!verify_checksum(cmd)) {
        send_response("[ERROR] Checksum inválido");
        return;
    }
    
}
