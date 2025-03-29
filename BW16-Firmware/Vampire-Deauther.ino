#include <WiFi.h>
#include "config.h"
#include "wifi_scan.h"
#include "wifi_attack.h"
#include "flipper_serial.h"
#include "flipper.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  delay(1000);
  
  // Configuración inicial WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  init_wifi_scan();
  init_wifi_attack();
  init_flipper_serial();
  
  Serial.println(F("[+] Vampire-Deauther BW16 Iniciado"));
}

void loop() {
  handle_flipper_serial();
  
  if(scan_active) {
    perform_scan();
  }
  
  if(attack_active) {
    execute_attack();
  }
  
  update_flipper_ui();
  delay(10);
}
