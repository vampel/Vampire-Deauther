#include "flipper_serial.h"
#include "scan.h"
#include "wifi_attack.h"

void initFlipperSerial() {
  // Inicialización del puerto serial para Flipper
}

void handleFlipperSerial() {
  if(Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if(cmd == "scan.start") {
      startScan();
      sendToFlipper("scan.status=1");
    }
    else if(cmd == "scan.stop") {
      stopScan();
      sendToFlipper("scan.status=0");
    }
    else if(cmd == "scan.results") {
      sendToFlipper(getScanResults());
    }
    else if(cmd.startsWith("attack.deauth ")) {
      int idx = cmd.substring(13).toInt();
      if(idx >= 0 && idx < networks.size()) {
        startDeauth(&networks[idx]);
        sendToFlipper("attack.status=1");
      }
    }
    else if(cmd == "attack.stop") {
      stopAttack();
      sendToFlipper("attack.status=0");
    }
  }
}

void sendToFlipper(const String& message) {
  Serial.println("FLP:" + message);  // Prefijo para identificar mensajes
}
