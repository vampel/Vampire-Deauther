#include <furi_hal_serial.h>
#include <furi.h>

#define UART_CHANNEL (&furi_hal_serial_control)  // Configuración UART

void uart_init() {
    furi_hal_serial_init(UART_CHANNEL, 115200);  // Mismo baud rate que BW16
}

void uart_send_command(const char* cmd) {
    furi_hal_serial_write(UART_CHANNEL, (uint8_t*)cmd, strlen(cmd));
    furi_hal_serial_write(UART_CHANNEL, (uint8_t*)"\n", 1);  // Terminador
}

// Ejemplo: Enviar comando desde la UI
void send_deauth_24ghz() {
    uart_send_command("DEAUTH24 AA:BB:CC:DD:EE:FF");
}
