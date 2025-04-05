#include "view_main.h"
#include <gui/elements.h>
#include <furi_hal_serial.h>
#include <furi_hal.h>
#include <string.h>

#define MENU_LEN    3
#define SERIAL_PORT ((FuriHalSerialId)1) // USART1: UART por GPIO del Flipper

const char* menu_items[MENU_LEN] = {
    "Scan WiFi",
    "Deauth Target",
    "Beacon Spam",
};

static int selected_index = 0;

void render_callback(Canvas* canvas, void* context) {
    UNUSED(context);
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    for(size_t i = 0; i < MENU_LEN; ++i) {
        bool selected = (i == selected_index);
        elements_bubble_str(canvas, 5, 15 + i * 15, AlignLeft, menu_items[i], selected);
    }
}

void input_callback(InputEvent* event, void* context) {
    ViewDispatcher* dispatcher = (ViewDispatcher*)context;
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyUp && selected_index > 0) {
            selected_index--;
        } else if(event->key == InputKeyDown && selected_index < (MENU_LEN - 1)) {
            selected_index++;
        } else if(event->key == InputKeyRight) {
            const char* command = NULL;
            if(selected_index == 0)
                command = "SCAN\n";
            else if(selected_index == 1)
                command = "DEAUTH\n";
            else if(selected_index == 2)
                command = "BEACON\n";

            if(command) {
                furi_hal_serial_tx(SERIAL_PORT, (const uint8_t*)command, strlen(command));
            }
        } else if(event->key == InputKeyLeft) {
            view_dispatcher_stop(dispatcher);
        }
    }
}

View* vampire_deauther_view_get(void) {
    View* view = view_alloc();
    view_set_draw_callback(view, render_callback);
    view_set_input_callback(view, input_callback);
    return view;
}
