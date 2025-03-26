#include "BTJammer.h"
void BTJammer::start() {
  WiFi.mode(WIFI_OFF); // Apaga WiFi
  BLEServer *pServer = BLEDevice::createServer();
  pServer->getAdvertising()->start();
}
