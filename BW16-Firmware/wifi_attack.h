#ifndef WIFI_ATTACK_H
#define WIFI_ATTACK_H

#include "wifi_scan.h"

extern bool attack_active;
extern WiFiNetwork* current_target;

void init_wifi_attack();
void execute_attack();
void start_deauth(WiFiNetwork* target);
void start_beacon(uint8_t channel, bool is_5ghz);
void stop_attack();

#endif
