#include "config.h"
#include "wifi_scan.h"
#include "wifi_attack.h"
#include "serial_protocol.h"
#include "flipper_ui.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  init_serial_protocol();
  init_flipper_ui();
  
  Serial.println("Vampire-Deauther BW16 Ready");
}

void loop() {
  handle_serial_commands();
  update_flipper_ui();
  
  if(scan_active) {
    perform_wifi_scan();
  }
  
  if(attack_active) {
    perform_attack();
  }
  
  delay(10);
}
