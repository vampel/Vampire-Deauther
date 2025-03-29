#include "bw16_protocol.h"

void bw16_send_command(VampireDeautherApp* app, BW16Command cmd, uint8_t* data, uint8_t len) {
    uint8_t buffer[len + 3];
    buffer[0] = 0xAA; // Header
    buffer[1] = cmd;  // Comando
    buffer[2] = len;  // Longitud
    
    if(len > 0 && data != NULL) {
        memcpy(&buffer[3], data, len);
    }
    
    furi_hal_serial_tx(app->serial_handle, buffer, len + 3);
}