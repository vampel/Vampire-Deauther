#ifndef CONFIG_H
#define CONFIG_H

// Configuración BW16
#define SERIAL_BAUDRATE 115200
#define MAX_NETWORKS 150
#define SCAN_INTERVAL 200

// Comandos Flipper
#define FLIPPER_CMD_SCAN_START "scan_start"
#define FLIPPER_CMD_ATTACK_DEAUTH "deauth"

// Canales optimizados
const uint8_t CHANNELS_2GHZ[] = {1, 6, 11};
const uint8_t CHANNELS_5GHZ[] = {36, 44, 48, 149, 153, 157};

#endif
