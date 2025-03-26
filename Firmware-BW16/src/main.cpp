#include "WiFiDeauth.h"
#include "BTJammer.h"
#include "uart/uart_handler.h"


}

void loop() {
    UARTHandler::read_commands();
}

void setup() {
    UARTHandler::init();
    WiFiDeauth::init();
  }
}

void loop() {
  // Espera comandos UART desde Flipper
}
