#include "flipper.h"

void updateFlipperUI() {
  // Implementación actualizada para usar flipper_serial
  if(scanActive) {
    sendToFlipper("ui:scan:running");
  } else {
    sendToFlipper("ui:scan:stopped");
  }
  
  if(attackActive && currentTarget) {
    String msg = "ui:attack:deauth:" + currentTarget->ssid;
    sendToFlipper(msg);
  }
}

void sendFlipperCommand(const String& cmd) {
  sendToFlipper("cmd:" + cmd);  // Usa la función de flipper_serial
}
