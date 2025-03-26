#include "mac_parser.h"

bool MACParser::parse(const String& mac_str, uint8_t* mac_out) {
    if (sscanf(mac_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
               &mac_out[0], &mac_out[1], &mac_out[2], 
               &mac_out[3], &mac_out[4], &mac_out[5]) == 6) {
        return true;
    }
    return false;
}
