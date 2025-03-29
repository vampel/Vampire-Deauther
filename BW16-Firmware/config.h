#ifndef CONFIG_H
#define CONFIG_H

// Configuración de Hardware
#define SERIAL_BAUDRATE 115200
#define MAX_NETWORKS 100

// Estados del sistema
#define SCAN_INACTIVE 0
#define SCAN_ACTIVE 1
#define ATTACK_INACTIVE 0
#define ATTACK_ACTIVE 1

// Comandos desde Flipper Zero
#define CMD_SCAN_START "SCAN"
#define CMD_SCAN_STOP "SCAN_STOP"
#define CMD_ATTACK_DEAUTH "DEAUTH"
#define CMD_ATTACK_BEACON "BEACON"
#define CMD_ATTACK_STOP "STOP"

// Canales WiFi optimizados
const uint8_t CHANNELS_2GHZ[] = {1, 6, 11};
const uint8_t CHANNELS_5GHZ[] = {36, 44, 149, 157};

#endif
