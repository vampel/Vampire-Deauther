#include <WiFi.h>
#include "config.h"
#include "wifi_scanner.h"
#include "wifi_attacker.h"
#include "flipper_serial.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  
  // Inicialización exclusiva WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  init_wifi_scanner();
  init_wifi_attacker();
  init_flipper_serial();
  
  Serial.println("[+] Vampire-Deauther BW16 Ready");
  Serial.println("[+] Bluetooth completamente deshabilitado");
}

void loop() {
  handle_flipper_commands();
  
  if(scan_status == SCAN_ACTIVE) {
    perform_wifi_scan();
  }
  
  if(attack_status == ATTACK_ACTIVE) {
    execute_wifi_attack();
  }
  
  delay(10);
}
