#pragma once
#include <WiFi.h>

class Stealth {
public:
    static void enable(uint8_t level = 3);
    static void randomize_mac();  // Unificada con randomize_identity()
    
    // Anti-Detección
    static void set_dynamic_delays();
private:
    static uint8_t generate_secure_byte();  // Única función de generación
};
