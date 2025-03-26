#include "Stealth.h"
#include <WiFi.h>

void Stealth::randomize_mac() {
    uint8_t mac[6];
    for (int i = 0; i < 6; i++) {
        mac[i] = generate_random_byte();
    }
    mac[0] &= 0xFE;  // MAC unicast
    mac[0] |= 0x02;   // MAC localmente administrada
    esp_wifi_set_mac(WIFI_IF_STA, mac);
}

void Stealth::set_random_intervals() {
    randomSeed(esp_random()); // Semilla HW segura
}

void Stealth::spoof_wifi_probes() {
    uint8_t fake_ssids[][32] = {"HomeNet", "OfficeWiFi", "FreeWifi"};
    wifi_send_pkt_freedom(/* Trama probe request */, 26, 0);
}

uint8_t Stealth::generate_random_byte() {
    return (uint8_t)(esp_random() % 256);
}


void Stealth::randomize_identity() {
    // MAC aleatoria válida (locally administered)
    uint8_t mac[6] = {0x02, generate_crypto_byte(), generate_crypto_byte(), 
                      generate_crypto_byte(), generate_crypto_byte(), generate_crypto_byte()};
    wifi_set_macaddr(SOFTAP_IF, mac);
    wifi_set_macaddr(STATION_IF, mac);
}

void Stealth::inject_dummy_traffic() {
    uint8_t dummy_frame[26] = {0x80, 0x00}; // Beacon frame
    wifi_send_pkt_freedom(dummy_frame, sizeof(dummy_frame), 0);
}
