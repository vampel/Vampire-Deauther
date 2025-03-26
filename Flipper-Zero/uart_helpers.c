void send_uart_command(const char* cmd) {
  furi_hal_serial_write(uart, (uint8_t*)cmd, strlen(cmd));
}
