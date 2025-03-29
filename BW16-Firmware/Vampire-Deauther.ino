#include <WiFi.h>
#include <BLEDevice.h>
#include "commands.h"

#define UART_BAUDRATE 115200

void setup() {
  Serial.begin(UART_BAUDRATE);  // UART con Flipper
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  BLEDevice::init("VampireBT"); // Inicializar BLE
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }
}
