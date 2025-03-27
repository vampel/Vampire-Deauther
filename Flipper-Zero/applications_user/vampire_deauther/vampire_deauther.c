#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <assets_icons.h>
#include <notification/notification.h>
#include "vampire_deauther.h"
#include <notification/notification_messages.h>

// Callbacks para WiFi
static void wifi_scan_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "SCAN\n", 5);
    notification_message(app->notifications, &sequence_blink_blue_100);
}

static void deauth_start_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "DEAUTH\n", 7);
    notification_message(app->notifications, &sequence_blink_red_100);
}

// Callbacks para Bluetooth Jamming
static void bt_jam_start_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_NOISE\n", 9);
    notification_message(app->notifications, &sequence_blink_green_100);
}

static void bt_jam_stop_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_STOP\n", 8);
    notification_message(app->notifications, &sequence_blink_red_100);
}

// Menú principal
static void draw_main_menu(VampireDeautherApp* app) {
    submenu_reset(app->submenu);
    submenu_add_item(app->submenu, "WiFi Scan", 0, wifi_scan_callback, app);
    submenu_add_item(app->submenu, "Start Deauth", 1, deauth_start_callback, app);
    submenu_add_item(app->submenu, "Start BT Noise", 2, bt_jam_start_callback, app);
    submenu_add_item(app->submenu, "Stop BT Noise", 3, bt_jam_stop_callback, app);
}

// Resto de funciones (init, event handlers, etc.)
// ... (mantén el código existente)
typedef enum {
    ViewMainMenu,
    ViewAttack,
    ViewSettings
} ViewCurrent;

typedef struct {
    ViewCurrent current_view;
    uint8_t menu_index;
    bool attack_running;
} AppState;

typedef struct {
    const char* text;
    const Icon* icon;
} MenuItem;

// Renderizado del menú principal
static void render_main_menu(Canvas* canvas, AppState* state) {
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignTop, "Vampire-Deauther");

    const MenuItem items[] = {
        {"WiFi 2.4GHz Deauth", &I_Wifi_10px},
        {"WiFi 5GHz Deauth", &I_Warning_10px},
        {"Bluetooth Jammer", &I_BLE_10px},
        {"Configuración", &I_Settings_10px}
    };

    for (size_t i = 0; i < COUNT_OF(items); i++) {
        canvas_draw_icon(canvas, 10, 30 + i * 13, items[i].icon);
        if (state->menu_index == i) {
            canvas_set_font(canvas, FontBold);
            canvas_draw_icon(canvas, 5, 30 + i * 13, &I_ButtonRight_4x7);
        } else {
            canvas_set_font(canvas, FontSecondary);
        }
        canvas_draw_str(canvas, 25, 30 + i * 13, items[i].text);
    }
}

// Renderizado durante el ataque
static void render_attack_view(Canvas* canvas, AppState* state) {
    const Icon* icons[] = {&I_Wifi_10px, &I_Warning_10px, &I_BLE_10px};
    canvas_draw_icon(canvas, 10, 10, icons[state->menu_index]);
    canvas_draw_str(canvas, 30, 20, "Atacando...");
    canvas_draw_str(canvas, 30, 40, "Presione BACK para detener");
}

// Manejador de inputs
static void input_handler(InputEvent* input, void* ctx) {
    AppState* state = ctx;
    if (input->type == InputTypePress) {
        switch (input->key) {
        case InputKeyUp:
            state->menu_index = (state->menu_index - 1) % 4;
            break;
        case InputKeyDown:
            state->menu_index = (state->menu_index + 1) % 4;
            break;
        case InputKeyOk:
            if (state->current_view == ViewMainMenu) {
                state->current_view = ViewAttack;
                state->attack_running = true;
                NotificationApp* notif = furi_record_open(RECORD_NOTIFICATION);
                notification_message(notif, &sequence_blink_cyan_100);
                furi_record_close(RECORD_NOTIFICATION);
            }
            break;
        case InputKeyBack:
            if (state->attack_running) {
                state->attack_running = false;
                NotificationApp* notif = furi_record_open(RECORD_NOTIFICATION);
                notification_message(notif, &sequence_reset_rgb);
                furi_record_close(RECORD_NOTIFICATION);
            }
            state->current_view = ViewMainMenu;
            break;
        }
    }
}

// Punto de entrada
int32_t vampire_deauther_app(void* p) {
    UNUSED(p);
    AppState* state = malloc(sizeof(AppState));
    state->current_view = ViewMainMenu;
    state->menu_index = 0;
    state->attack_running = false;

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, (ViewPortDrawCallback)render_callback, state);
    view_port_input_callback_set(view_port, input_handler, state);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    NotificationApp* notif = furi_record_open(RECORD_NOTIFICATION);

    // Bucle principal
    while (1) {
        view_port_update(view_port);
        furi_delay_ms(50);
    }

    // Limpieza (nunca alcanzado en este ejemplo)
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_NOTIFICATION);
    free(state);
    return 0;
}

// Añadir nuevos callbacks para BT
static void bt_jam_start_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_NOISE\n", 9);  // Envía comando
    notification_message(app->notifications, &sequence_blink_green_100);  // Feedback visual
}

static void bt_jam_stop_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_STOP\n", 8);  // Envía comando
    notification_message(app->notifications, &sequence_blink_red_100);
}
