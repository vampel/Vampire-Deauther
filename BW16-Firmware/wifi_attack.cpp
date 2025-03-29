// wifi_attack.cpp
#include "wifi_attack.h"
#include "config.h"

bool attack_active = false;
WiFiNetwork* selected_target = nullptr;

void init_wifi_attack() {
    // Inicialización de estructuras de ataque
}

void perform_attack() {
    if(!selected_target) return;
    
    // Implementación del ataque de deautenticación
    set_wifi_channel(selected_target->channel);
    
    // Paquete de deautenticación básico
    String cmd = "iwconfig wlan0 mode monitor channel ";
    cmd += selected_target->channel;
    system(cmd.c_str());
    
    // Aquí iría la lógica real de enviar paquetes de deautenticación
    // usando raw sockets o librerías específicas para BW16
}

void start_deauth(WiFiNetwork* target) {
    selected_target = target;
    attack_active = true;
}

void start_beacon_spam() {
    attack_active = true;
    // Implementación de beacon spam
}

void stop_attack() {
    attack_active = false;
    WiFi.mode(WIFI_STA);
}
