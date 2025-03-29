#ifndef CONFIG_H
#define CONFIG_H

// Configuración de hardware
#define SERIAL_BAUDRATE 115200
#define MAX_SCAN_NETWORKS 100
#define MAX_SSID_LENGTH 32

// Configuración de WiFi
#define CHANNEL_HOP_INTERVAL 200 // ms

// Comandos seriales para Flipper Zero
#define CMD_SCAN_START "SCAN_START"
#define CMD_SCAN_STOP "SCAN_STOP"
#define CMD_ATTACK_DEAUTH "ATTACK_DEAUTH"
#define CMD_ATTACK_BEACON "ATTACK_BEACON"
#define CMD_SELECT_TARGET "SELECT_TARGET"

#endif
