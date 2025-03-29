#ifndef CONFIG_H
#define CONFIG_H

// Configuración del Hardware BW16
#define SERIAL_BAUDRATE 115200  // Velocidad para comunicación con Flipper Zero
#define CHANNEL_HOP_INTERVAL 200 // ms entre cambios de canal

// Límites del sistema
#define MAX_SCAN_RESULTS 150     // Máximo redes a almacenar
#define MAX_SSID_LENGTH 32       // Longitud máxima para SSIDs
#define DEAUTH_PACKET_RATE 100   // ms entre paquetes de deauth

// Comandos para Flipper Zero (prefijo FLP:)
#define FLP_CMD_SCAN_START "scan.start"
#define FLP_CMD_SCAN_STOP "scan.stop"
#define FLP_CMD_SCAN_RESULTS "scan.results"
#define FLP_CMD_ATTACK_DEAUTH "attack.deauth"
#define FLP_CMD_ATTACK_STOP "attack.stop"
#define FLP_CMD_BEACON_SPAM "beacon.spam"

// Canales WiFi optimizados (2.4GHz y 5GHz)
const uint8_t CHANNELS_2GHZ[] = {1, 6, 11};  // Canales no superpuestos
const uint8_t CHANNELS_5GHZ[] = {36, 44, 48, 149, 153, 157, 161, 165};

// Tipos de ataque
#define ATTACK_TYPE_DEAUTH 0x01
#define ATTACK_TYPE_BEACON 0x02

// Estructura para configuración de red
typedef struct {
    uint8_t channel;
    bool is_5ghz;
    uint8_t bssid[6];
} wifi_target_t;

#endif // CONFIG_H
