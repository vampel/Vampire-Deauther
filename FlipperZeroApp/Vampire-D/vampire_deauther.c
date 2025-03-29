#include "vampire_deauther.h"
#include "bw16_protocol.h"

static void scan_view_draw_callback(Canvas* canvas, void* context) {
    VampireDeautherApp* app = context;
    canvas_draw_str(canvas, 10, 10, "Vampire-Deauther");
    
    if(app->ap_count == 0) {
        canvas_draw_str(canvas, 10, 20, "Presiona OK para escanear");
    } else {
        for(uint8_t i = 0; i < app->ap_count; i++) {
            char line[40];
            snprintf(line, sizeof(line), "%s (Ch %d)", 
                    app->access_points[i].ssid,
                    app->access_points[i].channel);
            canvas_draw_str(canvas, 10, 20 + (i * 10), line);
        }
    }
}

static void input_callback(InputEvent* event, void* context) {
    VampireDeautherApp* app = context;
    if(event->type == InputTypePress && event->key == InputKeyOk) {
        bw16_send_command(app, BW16_CMD_SCAN_APS, NULL, 0);
    }
}

int32_t vampire_deauther_app(void* p) {
    UNUSED(p);
    
    // Inicialización segura
    VampireDeautherApp* app = malloc(sizeof(VampireDeautherApp));
    furi_check(app);
    memset(app, 0, sizeof(VampireDeautherApp));
    
    // Configuración ViewPort
    app->view_port = view_port_alloc();
    view_port_draw_callback_set(app->view_port, scan_view_draw_callback, app);
    view_port_input_callback_set(app->view_port, input_callback, app);
    
    // Configuración serial
    app->serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);
    furi_check(app->serial_handle);
    furi_hal_serial_init(app->serial_handle, 115200);
    
    // Configuración GUI
    app->gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);
    
    // Bucle principal
    while(true) {
        view_port_update(app->view_port);
        furi_delay_ms(50);
    }
    
    // Limpieza (teóricamente inalcanzable)
    gui_remove_view_port(app->gui, app->view_port);
    view_port_free(app->view_port);
    furi_hal_serial_deinit(app->serial_handle);
    furi_record_close(RECORD_GUI);
    free(app);
    
    return 0;
}