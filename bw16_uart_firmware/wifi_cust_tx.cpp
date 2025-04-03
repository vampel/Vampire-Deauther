#include <Arduino.h>
#include "wifi_cust_tx.h"
#include "debug.h"

void wifi_cust_tx_init() {
    DEBUG_PRINTLN("[BW16] WiFi TX personalizado inicializado.");
}

void wifi_scan() {
    DEBUG_PRINTLN("[BW16] Escaneo iniciado...");
    delay(1000);
}

void deauth_attack(const char* target_mac) {
    DEBUG_PRINT("[BW16] Ataque Deauth a: ");
    DEBUG_PRINTLN(target_mac);
    delay(1000);
}

void beacon_spam(const char* ssid) {
    DEBUG_PRINT("[BW16] Spam de beacons con SSID: ");
    DEBUG_PRINTLN(ssid);
    delay(1000);
}
