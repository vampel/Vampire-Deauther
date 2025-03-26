#pragma once
#include <Arduino.h>

class Stealth {
public:
    static void enable();  // Activa todas las técnicas stealth
    static void randomize_mac();  
    static void set_random_intervals();
    static void spoof_wifi_probes();
private:
    static uint8_t generate_random_byte();
};

#pragma once
#include <WiFi.h>
#include <esp_wifi.h>

class Stealth {
public:
    static void enable(uint8_t intensity = 3); // 1-5 (stealth level)
    static void randomize_identity();
    static void set_dynamic_intervals(bool enable);
    
    // Anti-Forensics
    static void inject_dummy_traffic();
    static void avoid_dfs_channels();
private:
    static uint8_t generate_crypto_byte();
};
