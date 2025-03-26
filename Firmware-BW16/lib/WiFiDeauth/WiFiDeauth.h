#ifndef WIFI_DEAUTH_H
#define WIFI_DEAUTH_H

#include <Arduino.h>
#include <WiFi.h>          // Usar la librería WiFi real del BW16
#include <wl_definitions.h> // Para constantes WiFi

class WiFiDeauth {
public:
    // Inicialización (específica para RTL8720DN)
    static bool init();

    // Ataque Deauth (2.4GHz o 5GHz)
    static void start(bool is_5ghz, uint8_t* target_mac = nullptr);

private:
    // Configuración de canal (usando API Realtek)
    static void set_channel(uint8_t channel);

    // Envío de trama deauth (Low-Level Realtek)
    static void send_deauth(uint8_t* mac);

    // MAC de broadcast
    static const uint8_t broadcast_mac[6];
};

#endif
