#include "WiFiDeauth.h"
#include "BTJammer.h"

void setup() {
  Serial.begin(115200);
  if (!WiFiDeauth::init() || !BTJammer::init()) {
    Serial.println("[ERROR] Inicialización fallida");
    while(1);
  }
}

void loop() {
  // Espera comandos UART desde Flipper
}
