#include "vampire_deauther.h"
#include <gui/elements.h>
#include <notification/notification_messages.h>

/********************************** Callbacks **********************************/

static void submenu_callback(void* context, uint32_t index) {
    VampireDeautherApp* app = context;
    switch(index) {
    case 0: // Escanear redes
        view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewScan);
        break;
    case 1: // Ataques WiFi
        view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewAttack);
        break;
    case 2: // Configuración
        view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewSettings);
        break;
    case 3: // Acerca de
        view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewAbout);
        break;
    }
}

/********************************** Vistas *************************************/

static void scan_view_draw_callback(Canvas* canvas, void* context) {
    VampireDeautherApp* app = context;
    canvas_clear(canvas);
    elements_button_left(canvas, "Atrás");
    elements_button_right(canvas, "Escanear");
    
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignTop, "Escanear Redes");
    
    if(app->network_count > 0) {
        canvas_set_font(canvas, FontSecondary);
        for(uint8_t i = 0; i < MIN(app->network_count, 3); i++) {
            char info[64];
            snprintf(info, sizeof(info), "%s (CH:%d)", app->networks[i].ssid, app->networks[i].channel);
            canvas_draw_str_aligned(canvas, 64, 30 + (i * 12), AlignCenter, AlignTop, info);
        }
    } else {
        canvas_draw_str_aligned(canvas, 64, 30, AlignCenter, AlignTop, "No hay redes");
    }
}

static bool scan_view_input_callback(InputEvent* event, void* context) {
    VampireDeautherApp* app = context;
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyLeft) {
            view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewSubmenu);
            return true;
        } else if(event->key == InputKeyRight) {
            // Iniciar escaneo
            furi_hal_serial_tx(app->serial_handle, (uint8_t*)"SCAN_START\n", 11);
            app->scan_active = true;
            notification_message(app->notifications, &sequence_blink_start_blue);
            return true;
        }
    }
    return false;
}

static void attack_view_draw_callback(Canvas* canvas, void* context) {
    VampireDeautherApp* app = context;
    canvas_clear(canvas);
    elements_button_left(canvas, "Atrás");
    elements_button_center(canvas, "Detener");
    
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignTop, "Ataque Activo");
    
    if(app->current_target) {
        canvas_set_font(canvas, FontSecondary);
        char info[64];
        snprintf(info, sizeof(info), "Objetivo: %s", app->current_target->ssid);
        canvas_draw_str_aligned(canvas, 64, 30, AlignCenter, AlignTop, info);
    }
}

static bool attack_view_input_callback(InputEvent* event, void* context) {
    VampireDeautherApp* app = context;
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyLeft) {
            view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewSubmenu);
            return true;
        } else if(event->key == InputKeyOk) {
            // Detener ataque
            furi_hal_serial_tx(app->serial_handle, (uint8_t*)"ATTACK_STOP\n", 12);
            app->attack_active = false;
            notification_message(app->notifications, &sequence_blink_stop);
            return true;
        }
    }
    return false;
}

/********************************** Serial *************************************/

static int32_t serial_worker(void* context) {
    VampireDeautherApp* app = context;
    uint8_t buffer[64];
    
    while(1) {
        size_t len = furi_hal_serial_async_rx(app->serial_handle, buffer, sizeof(buffer), 50);
        if(len > 0) {
            // Procesar datos recibidos del BW16
            FURI_LOG_D(TAG, "Recibido: %.*s", len, buffer);
        }
    }
    return 0;
}

/********************************** Main App ***********************************/

int32_t vampire_deauther_app(void* p) {
    UNUSED(p);
    VampireDeautherApp* app = malloc(sizeof(VampireDeautherApp));
    
    // Inicialización básica
    app->gui = furi_record_open(RECORD_GUI);
    app->notifications = furi_record_open(RECORD_NOTIFICATION);
    app->view_dispatcher = view_dispatcher_alloc();
    
    // Configuración serial
    app->serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);
    furi_hal_serial_init(app->serial_handle, SERIAL_BAUDRATE);
    app->serial_thread = furi_thread_alloc_ex("SerialWorker", 1024, serial_worker, app);
    furi_thread_start(app->serial_thread);
    
    // Menú principal
    app->submenu = submenu_alloc();
    submenu_add_item(app->submenu, "Escanear Redes", 0, submenu_callback, app);
    submenu_add_item(app->submenu, "Ataques WiFi", 1, submenu_callback, app);
    submenu_add_item(app->submenu, "Configuración", 2, submenu_callback, app);
    submenu_add_item(app->submenu, "Acerca de", 3, submenu_callback, app);
    view_dispatcher_add_view(app->view_dispatcher, VampireDeautherViewSubmenu, submenu_get_view(app->submenu));
    
    // Vista de escaneo
    app->scan_view = widget_alloc();
    widget_set_draw_callback(app->scan_view, scan_view_draw_callback, app);
    widget_set_input_callback(app->scan_view, scan_view_input_callback, app);
    view_dispatcher_add_view(app->view_dispatcher, VampireDeautherViewScan, widget_get_view(app->scan_view));
    
    // Vista de ataque
    app->attack_view = widget_alloc();
    widget_set_draw_callback(app->attack_view, attack_view_draw_callback, app);
    widget_set_input_callback(app->attack_view, attack_view_input_callback, app);
    view_dispatcher_add_view(app->view_dispatcher, VampireDeautherViewAttack, widget_get_view(app->attack_view));
    
    // Configurar navegación
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(app->view_dispatcher, VampireDeautherViewSubmenu);
    
    // Ejecutar aplicación
    view_dispatcher_run(app->view_dispatcher);
    
    // Limpieza
    furi_thread_flags_set(furi_thread_get_id(app->serial_thread), FuriFlagExit);
    furi_thread_join(app->serial_thread);
    furi_thread_free(app->serial_thread);
    
    view_dispatcher_remove_view(app->view_dispatcher, VampireDeautherViewSubmenu);
    view_dispatcher_remove_view(app->view_dispatcher, VampireDeautherViewScan);
    view_dispatcher_remove_view(app->view_dispatcher, VampireDeautherViewAttack);
    
    widget_free(app->scan_view);
    widget_free(app->attack_view);
    submenu_free(app->submenu);
    view_dispatcher_free(app->view_dispatcher);
    
    furi_hal_serial_deinit(app->serial_handle);
    furi_hal_serial_control_release(app->serial_handle);
    
    furi_record_close(RECORD_NOTIFICATION);
    furi_record_close(RECORD_GUI);
    
    free(app);
    return 0;
}
