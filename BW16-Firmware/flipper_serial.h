#ifndef FLIPPER_SERIAL_H
#define FLIPPER_SERIAL_H

void init_flipper_serial();
void handle_flipper_serial();
void send_to_flipper(const String& data);

#endif
