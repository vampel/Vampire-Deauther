#include "uart_handler.h"
#include "WiFiDeauth.h"  // Para ejecutar comandos

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
    // ... otros comandos (DEAUTH5, BTJAM, etc.)
}

void UARTHandler::send_response(const String& message) {
    Serial.println(message);
}
