#ifndef FLIPPER_SERIAL_H
#define FLIPPER_SERIAL_H

#include "config.h"
#include "wifi_scanner.h"
#include "wifi_attack.h"

void init_flipper_serial();
void handle_flipper_commands();
void send_to_flipper(const String& message);

#endif
