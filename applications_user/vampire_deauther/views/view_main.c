#include "view_main.h"
#include <gui/elements.h>
#include <furi.h>

const char* menu_options[] = {
    "Scan WiFi",
    "Deauth",
    "Beacon",
};

static int selected_index = 0;
#define MENU_LEN (sizeof(menu_options) / sizeof(menu_options[0]))

void render_callback(Canvas* canvas, void* context) {
    UNUSED(context);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);

    for(uint8_t i = 0; i < MENU_LEN; i++) {
        elements_bubble_str(
            canvas,
            5,
            15 + i * 12,
            menu_options[i],
            (i == selected_index) ? AlignLeft : AlignRight,
            (i == selected_index));
    }
}

bool input_callback(InputEvent* event, void* context) {
    UNUSED(context);

    if(event->type == InputTypeShort) {
        if(event->key == InputKeyUp && selected_index > 0) {
            selected_index--;
            return true;
        } else if(event->key == InputKeyDown && selected_index < (MENU_LEN - 1)) {
            selected_index++;
            return true;
        } else if(event->key == InputKeyOk) {
            // Aquí puedes enviar comandos al BW16 por UART
            furi_hal_uart_tx(FURI_HAL_UART_ID_EXTERNAL, "CMD\n", 4);
            return true;
        }
    }
    return false;
}
