#include <WiFi.h>
#include "scan.h"
#include "attack.h"
#include "serial.h"
#include "flipper.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Inicialización WiFi exclusiva (sin Bluetooth)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  initScan();
  initAttack();
  initSerial();
  
  Serial.println(F("[VAMPIRE] Firmware iniciado (2.4GHz/5GHz)"));
}

void loop() {
  handleSerial();
  
  if(scanActive) {
    channelHop();
    performScan();
  }
  
  if(attackActive) {
    executeAttack();
  }
  
  updateFlipper();
  delay(10);
}
