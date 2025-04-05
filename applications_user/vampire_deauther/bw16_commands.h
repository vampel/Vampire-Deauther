#pragma once

// Comandos BW16 (compatibles con tu firmware .ino)
#define BW16_CMD_INIT     "INIT\n"
#define BW16_CMD_SCAN_AP  "SCANAP\n"
#define BW16_CMD_SCAN_STA "SCANSTA\n"
#define BW16_CMD_DEAUTH   "DEAUTH "
#define BW16_CMD_STOP     "STOP\n"

// Timeouts para 9600 baudios
#define BW16_CTRL_ACTIVE_MS 50
#define BW16_CHAR_DELAY_MS  3
#define BW16_ACK_TIMEOUT_MS 500
