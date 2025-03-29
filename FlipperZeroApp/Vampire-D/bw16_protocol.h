#pragma once
#include "vampire_deauther.h"

typedef enum {
    BW16_CMD_SCAN_APS = 0x01,
    BW16_CMD_DEAUTH = 0x02
} BW16Command;

void bw16_send_command(VampireDeautherApp* app, BW16Command cmd, uint8_t* data, uint8_t len);