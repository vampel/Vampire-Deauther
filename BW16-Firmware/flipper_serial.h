#ifndef FLIPPER_SERIAL_H
#define FLIPPER_SERIAL_H

void initFlipperSerial();
void handleFlipperSerial();
void sendToFlipper(const String& message);

#endif
