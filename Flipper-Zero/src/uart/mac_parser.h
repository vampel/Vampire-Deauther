#pragma once
#include <Arduino.h>

class MACParser {
public:
    static bool parse(const String& mac_str, uint8_t* mac_out);
};
