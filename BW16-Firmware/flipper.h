#ifndef FLIPPER_H
#define FLIPPER_H

#include "flipper_serial.h"  // Cambiado de serial.h
#include "scan.h"
#include "wifi_attack.h"

void updateFlipperUI();
void sendFlipperCommand(const String& cmd);

#endif
