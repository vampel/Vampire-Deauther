#include <Arduino.h>
#include "wifi_cust_tx.h"

String input_serial;

void setup() {
    Serial.begin(9600);
    while (!Serial);  // Esperar conexión serial

    Serial.println("[BW16] Vampire-Deauther inicializado");
    wifi_cust_tx_init();  // Inicializa funciones WiFi personalizadas
}

void loop() {
    if (Serial.available()) {
        input_serial = Serial.readStringUntil('\n');
        input_serial.trim();  // Elimina espacios y saltos de línea

        if (input_serial == "SCAN") {
            wifi_scan();
        } else if (input_serial.startsWith("DEAUTH ")) {
            String target = input_serial.substring(7);
            deauth_attack(target.c_str());
        } else if (input_serial.startsWith("BEACON ")) {
            String ssid = input_serial.substring(7);
            beacon_spam(ssid.c_str());
        } else {
            Serial.println("[BW16] Comando no reconocido");
        }
    }
}
