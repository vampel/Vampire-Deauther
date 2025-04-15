#include <gui/view.h>
#include <gui/canvas.h>
#include <furi_hal.h>
#include "view_main.h"

#define GPIO_OUT_PIN &gpio_ext_pb3  // Flipper GPIO 15 -> BW16 PA12

static const char* menu_items[] = {
    "Scan",
    "Deauth",
    "Beacon",
};

static int selected_index = 0;
static bool command_sent = false;

static void draw_callback(Canvas* canvas, void* context) {
    UNUSED(context);
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);

    int item_height = 14;
    int menu_height = item_height * 3;
    int y_start = (64 - menu_height) / 2;

    for(size_t i = 0; i < 3; ++i) {
        const char* text = menu_items[i];
        int text_width = canvas_string_width(canvas, text);
        int x = (128 - text_width) / 2;
        int y = y_start + i * item_height;

        if((int)i == selected_index && !command_sent) {
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_box(canvas, x - 2, y - 1, text_width + 4, 12);
            canvas_set_color(canvas, ColorWhite);
        } else {
            canvas_set_color(canvas, ColorBlack);
        }

        canvas_draw_str(canvas, x, y + 8, text);
    }

    if(command_sent) {
        const char* action = NULL;
        if(selected_index == 0) action = "Sending: Scan...";
        else if(selected_index == 1) action = "Sending: Deauth...";
        else if(selected_index == 2) action = "Sending: Beacon...";

        canvas_set_font(canvas, FontPrimary);
        uint16_t text_width = canvas_string_width(canvas, action);
        uint16_t x = (128 - text_width) / 2;
        uint16_t y = 64 - 4; // más abajo sin salirse

        canvas_set_color(canvas, ColorBlack);
        canvas_draw_box(canvas, x - 2, y - 9, text_width + 4, 12);
        canvas_set_color(canvas, ColorWhite);
        canvas_draw_str(canvas, x, y, action);
    }
}

static bool input_callback(InputEvent* event, void* context) {
    UNUSED(context);

    if(event->type == InputTypePress) {
        if(!command_sent) {
            if(event->key == InputKeyUp) {
                if(selected_index > 0) selected_index--;
            } else if(event->key == InputKeyDown) {
                if(selected_index < 2) selected_index++;
            } else if(event->key == InputKeyOk) {
                furi_hal_gpio_write(GPIO_OUT_PIN, true);
                command_sent = true;
            }
        } else if(event->key == InputKeyBack) {
            furi_hal_gpio_write(GPIO_OUT_PIN, false);
            command_sent = false;
            return false;
        }
    }
    return true;
}

View* vampire_deauther_view_get(void) {
    furi_hal_gpio_init_simple(GPIO_OUT_PIN, GpioModeOutputPushPull);

    View* view = view_alloc();
    view_set_draw_callback(view, draw_callback);
    view_set_input_callback(view, input_callback);
    return view;
}
