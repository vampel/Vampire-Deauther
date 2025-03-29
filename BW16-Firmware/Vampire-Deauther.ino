#include <WiFi.h>
#include "scan.h"
#include "wifi_attack.h"
#include "flipper_serial.h"  // Cambiado de serial.h
#include "flipper.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  initScan();
  initWifiAttack();
  initFlipperSerial();  // Cambiado de initSerial()
  
  Serial.println(F("[VAMPIRE] Firmware iniciado (2.4GHz/5GHz)"));
}

void loop() {
  handleFlipperSerial();  // Cambiado de handleSerial()
  
  if(scanActive) {
    channelHop();
    performScan();
  }
  
  if(attackActive) {
    executeWifiAttack();
  }
  
  updateFlipper();
  delay(10);
}
