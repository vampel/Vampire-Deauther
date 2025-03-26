#pragma once
#include <Arduino.h>

class UARTHandler {
public:
    static void init(uint32_t baud_rate = 115200);
    static void read_commands();
    static void send_response(const String& message);

private:
    static void parse_command(const String& cmd);
};
