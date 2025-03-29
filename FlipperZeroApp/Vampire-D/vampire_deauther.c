#include "vampire_deauther.h"
#include <furi_hal_serial.h>
#include <gui/elements.h>
#include <notification/notification_messages.h>

static void attack_view_draw_callback(Canvas* canvas, void* context) {
    UNUSED(context);
    canvas_clear(canvas);
    elements_button_left(canvas, "Regresar");
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignTop, "Ataque Activo");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str_aligned(canvas, 64, 30, AlignCenter, AlignTop, "Presione OK para detener");
}

static bool attack_view_input_callback(InputEvent* input_event, void* context) {
    VampireDeautherApp* app = context;
    
    if(input_event->type == InputTypeShort) {
        if(input_event->key == InputKeyBack || input_event->key == InputKeyLeft) {
            // Detener ataque y regresar
            furi_hal_serial_tx(app->serial_handle, (uint8_t*)"STOP\n", 5);
            app->attack_active = false;
            notification_message(app->notifications, &sequence_blink_stop);
            view_dispatcher_switch_to_view(app->view_dispatcher, 0);
        }
    }
    return true;
}

static void wifi_attack_callback(void* context, uint32_t index) {
    UNUSED(index);
    VampireDeautherApp* app = context;
    furi_hal_serial_tx(app->serial_handle, (uint8_t*)"WIFI_START\n", 11);
    app->attack_active = true;
    view_dispatcher_switch_to_view(app->view_dispatcher, 1);
    notification_message(app->notifications, &sequence_blink_start_blue);
}

static void bt_jammer_callback(void* context, uint32_t index) {
    UNUSED(index);
    VampireDeautherApp* app = context;
    furi_hal_serial_tx(app->serial_handle, (uint8_t*)"BT_START\n", 9);
    app->attack_active = true;
    view_dispatcher_switch_to_view(app->view_dispatcher, 1);
    notification_message(app->notifications, &sequence_blink_start_red);
}

static void ble_spam_callback(void* context, uint32_t index) {
    UNUSED(index);
    VampireDeautherApp* app = context;
    furi_hal_serial_tx(app->serial_handle, (uint8_t*)"BLE_START\n", 10);
    app->attack_active = true;
    view_dispatcher_switch_to_view(app->view_dispatcher, 1);
    notification_message(app->notifications, &sequence_blink_start_green);
}

int32_t vampire_deauther_app(void* p) {
    UNUSED(p);
    
    VampireDeautherApp* app = malloc(sizeof(VampireDeautherApp));
    app->attack_active = false;
    
    // Inicializar serial
    app->serial_handle = furi_hal_serial_control_acquire(FuriHalSerialIdUsart);
    furi_check(app->serial_handle);
    furi_hal_serial_init(app->serial_handle, 115200);
    
    // Configurar GUI
    app->gui = furi_record_open(RECORD_GUI);
    app->notifications = furi_record_open(RECORD_NOTIFICATION);
    app->view_dispatcher = view_dispatcher_alloc();
    
    // Configurar menú principal
    app->submenu = submenu_alloc();
    view_dispatcher_add_view(app->view_dispatcher, 0, submenu_get_view(app->submenu));
    
    // Configurar vista de ataque
    app->attack_view = widget_alloc();
    view_set_draw_callback(widget_get_view(app->attack_view), attack_view_draw_callback);
    view_set_input_callback(widget_get_view(app->attack_view), attack_view_input_callback);
    view_set_context(widget_get_view(app->attack_view), app);
    view_dispatcher_add_view(app->view_dispatcher, 1, widget_get_view(app->attack_view));
    
    // Configurar items del menú
    submenu_add_item(app->submenu, "WiFi Deauther", 0, wifi_attack_callback, app);
    submenu_add_item(app->submenu, "BT Jammer", 1, bt_jammer_callback, app);
    submenu_add_item(app->submenu, "BLE Spam", 2, ble_spam_callback, app);
    
    // Configurar navegación
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);
    
    // Ejecutar aplicación
    view_dispatcher_run(app->view_dispatcher);
    
    // Limpieza
    if(app->attack_active) {
        furi_hal_serial_tx(app->serial_handle, (uint8_t*)"STOP\n", 5);
    }
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