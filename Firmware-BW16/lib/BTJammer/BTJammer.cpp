#include "BTJammer.h"
void BTJammer::start() {
  WiFi.mode(WIFI_OFF); // Apaga WiFi
  BLEServer *pServer = BLEDevice::createServer();
  pServer->getAdvertising()->start();
}

void BTJammer::start() {
    WiFi.mode(WIFI_OFF); // Libera antena
    BLEDevice::init("Fake Device");
    while (true) {
        BLEServer *pServer = BLEDevice::createServer();
        pServer->getAdvertising()->setMinInterval(20); // Spam rápido
        pServer->getAdvertising()->start();
        delay(50);
    }
}
