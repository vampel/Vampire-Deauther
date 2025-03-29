#ifndef WIFI_ATTACK_H
#define WIFI_ATTACK_H

#include "config.h"
#include "wifi_scanner.h"

extern uint8_t attack_status;
extern WiFiNetwork* current_target;

void init_wifi_attacker();
void execute_wifi_attack();
void start_deauth_attack(WiFiNetwork* target);
void start_beacon_spam();
void stop_all_attacks();

#endif
