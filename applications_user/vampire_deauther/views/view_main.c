#include "view_main.h"
#include <gui/elements.h>
#include <notification/notification_messages.h>
#include <string.h>

extern FuriHalSerialHandle* serial_handle;
extern const GpioPin gpio_bw16_ctrl;
extern const GpioPin gpio_bw16_status;

static NotificationApp* notification = NULL;

bool input_callback(InputEvent* event, void* context) {
    VampireDeautherModel* model = context;

    if(event->type == InputTypePress) {
        switch(event->key) {
        case InputKeyUp:
            model->selected_index = model->selected_index > 0 ? model->selected_index - 1 : 2;
            break;
        case InputKeyDown:
            model->selected_index = model->selected_index < 2 ? model->selected_index + 1 : 0;
            break;
        case InputKeyOk:
            if(!model->scanning && !model->attacking) {
                switch(model->selected_index) {
                case 0: // Scan AP
                    model->scanning = true;
                    break;
                case 1: // Deauth
                    model->attacking = true;
                    break;
                case 2: // Stop
                    // Enviar comando STOP
                    break;
                }
            }
            break;
        case InputKeyBack:
            if(model->scanning || model->attacking) {
                model->scanning = false;
                model->attacking = false;
            }
            break;
        }
    }
    return true;
}

void render_callback(Canvas* canvas, void* context) {
    VampireDeautherModel* model = context;
    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);

    // Marco de la interfaz
    elements_frame(canvas, 0, 0, 128, 64);

    if(model->scanning) {
        canvas_draw_str_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "Scanning...");
    } else if(model->attacking) {
        canvas_draw_str_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "Deauth Running");
    } else {
        const char* menu_items[] = {"Scan APs", "Start Deauth", "Stop All"};
        for(uint8_t i = 0; i < 3; i++) {
            canvas_draw_str(canvas, 10, 16 + (i * 11), menu_items[i]);
            if(model->selected_index == i) {
                elements_frame(canvas, 8, 6 + (i * 11), 112, 12);
            }
        }
    }
}

View* vampire_deauther_view_get(void) {
    View* view = view_alloc();
    VampireDeautherModel* model = malloc(sizeof(VampireDeautherModel));
    memset(model, 0, sizeof(VampireDeautherModel));

    view_set_context(view, model);
    view_set_input_callback(view, input_callback);
    view_set_draw_callback(view, render_callback);

    return view;
}
