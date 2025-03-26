#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <BLEDevice.h>

class Core {
public:
    // Inicialización
    static bool begin();

    // WiFi Deauth (2.4GHz + 5GHz)
    static void wifi_attack(bool stealth_mode, const uint8_t* target_mac = nullptr);

    // Bluetooth Jammer
    static void bt_jam(bool random_mac);

    // Stealth
    static void enable_stealth(uint8_t level = 3);
private:
    static void send_deauth_frame(const uint8_t* mac, uint8_t channel);
    static void randomize_mac();
};
