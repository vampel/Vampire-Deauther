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
