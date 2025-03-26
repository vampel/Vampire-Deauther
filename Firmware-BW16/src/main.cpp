#include <WiFi.h>
#include <BLEDevice.h>
#include "commands.h"
#include "WiFiDeauth.h"
#include "BTJammer.h"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  BLEDevice::init(""); // Inicializa BLE
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    if (cmd == CMD_DEAUTH_24GHZ) WiFiDeauth::start(false); // 2.4GHz
    else if (cmd == CMD_DEAUTH_5GHZ) WiFiDeauth::start(true); // 5GHz
    else if (cmd == CMD_BT_JAMMER) BTJammer::start();
  }
}
