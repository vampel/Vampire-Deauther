#include "wifi_attack.h"
#include <WiFi.h>

bool attack_active = false;
WiFiNetwork* current_target = nullptr;

void init_wifi_attack() {
  // Inicialización específica BW16
}

void execute_attack() {
  if(!current_target) return;
  
  set_channel(current_target->channel);
  
  // Implementación de ataque basada en WiFiX
  String cmd = "iwconfig wlan0 mode monitor channel ";
  cmd += current_target->channel;
  system(cmd.c_str());
  
  // Lógica de envío de paquetes...
}

void start_deauth(WiFiNetwork* target) {
  current_target = target;
  attack_active = true;
  Serial.print(F("[ATTACK] Deauth iniciado: "));
  Serial.println(target->ssid);
}

void stop_attack() {
  attack_active = false;
  WiFi.mode(WIFI_STA);
  Serial.println(F("[ATTACK] Detenido"));
}
