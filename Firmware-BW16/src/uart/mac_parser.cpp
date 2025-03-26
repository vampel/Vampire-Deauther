#include "mac_parser.h"

bool MACParser::parse(const String& mac_str, uint8_t* mac_out) {
    // Permite formatos: "AA:BB:CC:DD:EE:FF" o "AABBCCDDEEFF"
    if (sscanf(mac_str.c_str(), "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx", 
               &mac_out[0], &mac_out[1], &mac_out[2],
               &mac_out[3], &mac_out[4], &mac_out[5]) == 6) {
        return true;
    } else if (mac_str.length() == 12) { // Sin separadores
        for (int i = 0; i < 6; i++) {
            if (sscanf(mac_str.c_str() + i*2, "%2hhx", &mac_out[i]) != 1) {
                return false;
            }
        }
        return true;
    }
    return false;
}
