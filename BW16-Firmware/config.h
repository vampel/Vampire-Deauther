#ifndef CONFIG_H
#define CONFIG_H

// Configuración BW16
#define SERIAL_BAUDRATE 115200
#define MAX_NETWORKS 150
#define DEAUTH_RATE_MS 100

// Comandos Flipper Zero
#define CMD_SCAN_START "scan_start"
#define CMD_SCAN_STOP "scan_stop"
#define CMD_DEAUTH "deauth"
#define CMD_BEACON "beacon"
#define CMD_STOP "stop"

// Canales WiFi optimizados
const uint8_t CH_2GHZ[] = {1, 6, 11};
const uint8_t CH_5GHZ[] = {36, 44, 48, 149, 153, 157, 161, 165};

#endif
