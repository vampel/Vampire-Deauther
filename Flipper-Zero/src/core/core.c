#include <furi.h>
#include <furi_hal.h>

void send_command(const char* cmd) {
    furi_hal_serial_write(uart, (uint8_t*)cmd, strlen(cmd));
}

void attack_callback() {
    send_command("ATTACK");
    vibrate(200); // Feedback táctil
}
