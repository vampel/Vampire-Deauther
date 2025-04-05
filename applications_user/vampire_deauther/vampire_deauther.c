#include "vampire_deauther.h"
#include "views/view_main.h"
#include <furi_hal_power.h>

// Definición exacta de pines según tu conexión
const GpioPin gpio_bw16_ctrl = {
    .port = GPIOA,
    .pin = LL_GPIO_PIN_12}; // Pin 5 (Azul) -> Flipper Pin 15
const GpioPin gpio_bw16_status = {
    .port = GPIOA,
    .pin = LL_GPIO_PIN_13}; // Pin 6 (Verde) -> Flipper Pin 16

void bw16_init_serial(VampireDeautherApp* app) {
    // Configuración GPIO exacta
    furi_hal_gpio_init(&gpio_bw16_ctrl, GpioModeOutputPushPull, GpioPullNo, GpioSpeedLow);
    furi_hal_gpio_init(&gpio_bw16_status, GpioModeInput, GpioPullUp, GpioSpeedLow);
    furi_hal_gpio_write(&gpio_bw16_ctrl, false);

    // Configuración UART específica para BW16
    app->serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);
    furi_hal_serial_set_br(app->serial_handle, 9600); // Compatible con Serial.begin(9600)
    furi_hal_serial_enable_tx(app->serial_handle);
}

bool bw16_send_command(VampireDeautherApp* app, const char* command) {
    // Activar línea de control (PA12 -> Pin 15 Flipper)
    furi_hal_gpio_write(&gpio_bw16_ctrl, true);
    furi_delay_ms(BW16_CTRL_ACTIVE_MS);

    // Envío carácter por carácter (necesario a 9600 baudios)
    for(size_t i = 0; i < strlen(command); i++) {
        furi_hal_serial_tx(app->serial_handle, (uint8_t*)&command[i], 1);
        furi_delay_ms(BW16_CHAR_DELAY_MS);
    }

    // Esperar ACK por PA13 (Pin 16 Flipper)
    uint32_t timeout = furi_get_tick() + BW16_ACK_TIMEOUT_MS;
    while(furi_get_tick() < timeout) {
        if(furi_hal_gpio_read(&gpio_bw16_status)) {
            furi_hal_gpio_write(&gpio_bw16_ctrl, false);
            return true;
        }
        furi_delay_ms(10);
    }
    return false;
}

int32_t vampire_deauther_app(void* p) {
    UNUSED(p);

    VampireDeautherApp* app = malloc(sizeof(VampireDeautherApp));
    app->gui = furi_record_open(RECORD_GUI);
    app->view_dispatcher = view_dispatcher_alloc();

    // Inicialización hardware exacta
    furi_hal_power_enable_otg();
    bw16_init_serial(app);

    // Enviar comando INIT al BW16
    app->bw16_ready = bw16_send_command(app, BW16_CMD_INIT);

    // Configurar vista principal
    app->main_view = vampire_deauther_view_get();
    view_dispatcher_add_view(app->view_dispatcher, 0, app->main_view);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    view_dispatcher_run(app->view_dispatcher);

    // Limpieza específica
    bw16_send_command(app, BW16_CMD_STOP);
    furi_hal_serial_disable_tx(app->serial_handle);
    furi_hal_serial_control_release(app->serial_handle);
    view_dispatcher_remove_view(app->view_dispatcher, 0);
    view_dispatcher_free(app->view_dispatcher);
    furi_record_close(RECORD_GUI);
    free(app);
    furi_hal_power_disable_otg();

    return 0;
}
