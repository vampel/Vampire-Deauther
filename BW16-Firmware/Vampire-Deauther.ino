#include <WiFi.h>
#include "config.h"
#include "wifi_scanner.h"
#include "wifi_attack.h"
#include "flipper_serial.h"
#include "flipper.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  
  // Inicialización WiFi exclusiva
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  init_wifi_scanner();
  init_wifi_attack();
  init_flipper_serial();
  
  Serial.println(F("[VAMPIRE] BW16 Firmware Ready"));
}

void loop() {
  handle_flipper_serial();
  
  if(scan_active) {
    perform_wifi_scan();
  }
  
  if(attack_active) {
    execute_wifi_attack();
  }
  
  update_flipper_interface();
  delay(10);
}
