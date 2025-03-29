#include "wifi_attack.h"
#include <WiFi.h>

uint8_t attack_status = ATTACK_INACTIVE;
WiFiNetwork* current_target = nullptr;

void init_wifi_attacker() {
  // Inicialización específica para ataques
}

void execute_wifi_attack() {
  if(!current_target) return;
  
  set_wifi_channel(current_target->channel);
  
  // Ejemplo básico de comando de deautenticación
  String cmd = "iwconfig wlan0 mode monitor channel ";
  cmd += current_target->channel;
  system(cmd.c_str());
  
  // Aquí iría la lógica real de envío de paquetes deauth
  // usando raw sockets o librerías específicas
}

void start_deauth_attack(WiFiNetwork* target) {
  current_target = target;
  attack_status = ATTACK_ACTIVE;
  Serial.println("[+] Deauth attack started on: " + target->ssid);
}

void start_beacon_spam() {
  attack_status = ATTACK_ACTIVE;
  Serial.println("[+] Beacon spam started");
}

void stop_all_attacks() {
  attack_status = ATTACK_INACTIVE;
  WiFi.mode(WIFI_STA);
  Serial.println("[+] All attacks stopped");
}
