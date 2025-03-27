#include "ui.c"  // Integra la UI

// Nueva función para manejar inputs
void handle_input(InputEvent* event) {
    if(event->type == InputTypePress) {
        if(event->key == InputKeyOk) {
            ui_draw_callback(canvas, (void*)1);  // Muestra pantalla de ataque
        }
    }
}

// Inicialización (actualizada)
void core_init() {
    view_port_draw_callback_set(view_port, ui_draw_callback, NULL);
    view_port_input_callback_set(view_port, handle_input);
}


uart_send_command("DEAUTH 2.4GHz STEALTH");
uart_send_command("BTJAM RANDOM_MAC");
