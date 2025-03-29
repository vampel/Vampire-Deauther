// wifi_attack.h
#ifndef WIFI_ATTACK_H
#define WIFI_ATTACK_H

#include "wifi_scan.h"

extern bool attack_active;
extern WiFiNetwork* selected_target;

void init_wifi_attack();
void perform_attack();
void start_deauth(WiFiNetwork* target);
void start_beacon_spam();
void stop_attack();

#endif
