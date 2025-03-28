/* applications_user/vampire_deauther/vampire_deauther.c */
#include "vampire_deauther.h"
#include <furi_hal_uart.h>
#include <notification/notification_messages.h>

// ============== WiFi Deauther Menu ==============
static void wifi_all_deauth_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "WIFI_DEAUTH_ALL\n", 16);
    notification_message(app->notifications, &sequence_blink_red_100);
}

static void wifi_24ghz_deauth_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "WIFI_DEAUTH_24\n", 15);
    notification_message(app->notifications, &sequence_blink_blue_100);
}

static void wifi_5ghz_deauth_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "WIFI_DEAUTH_5\n", 14);
    notification_message(app->notifications, &sequence_blink_green_100);
}

static void wifi_deauther_menu_callback(void* context) {
    VampireDeautherApp* app = context;
    submenu_reset(app->submenu);
    
    submenu_add_item(app->submenu, "WiFi All Deauth", 0, wifi_all_deauth_callback, app);
    submenu_add_item(app->submenu, "WiFi 2.4GHz Deauth", 1, wifi_24ghz_deauth_callback, app);
    submenu_add_item(app->submenu, "WiFi 5GHz Deauth", 2, wifi_5ghz_deauth_callback, app);
}

// ============== BT Jammer Menu ==============
static void bt_jam_all_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_ALL\n", 11);
    notification_message(app->notifications, &sequence_blink_magenta_100);
}

static void bt_jam_classic_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_CLASSIC\n", 15);
    notification_message(app->notifications, &sequence_blink_cyan_100);
}

static void bt_jam_ble_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_BLE\n", 11);
    notification_message(app->notifications, &sequence_blink_yellow_100);
}

static void bt_jammer_menu_callback(void* context) {
    VampireDeautherApp* app = context;
    submenu_reset(app->submenu);
    
    submenu_add_item(app->submenu, "BT Jammer All", 0, bt_jam_all_callback, app);
    submenu_add_item(app->submenu, "BT Jammer Classic", 1, bt_jam_classic_callback, app);
    submenu_add_item(app->submenu, "BT Jammer BLE", 2, bt_jam_ble_callback, app);
}

// ============== Settings Menu ==============
static void set_channel_callback(void* context) {
    // Implementa selección de canal como en Marauder
    VampireDeautherApp* app = context;
    variable_item_set_current_value_index(app->channel_item, app->channel_index);
    furi_hal_uart_tx(app->uart, "SET_CH=", 7);
    furi_hal_uart_tx(app->uart, (uint8_t*)&app->channel_index, 1);
}

static void settings_menu_callback(void* context) {
    VampireDeautherApp* app = context;
    variable_item_list_reset(app->var_item_list);
    
    app->channel_item = variable_item_list_add(
        app->var_item_list, 
        "WiFi Channel", 
        14,  // Número de canales 2.4GHz
        set_channel_callback, 
        app
    );
    
    variable_item_set_current_value_index(app->channel_item, app->channel_index);
}

// ============== Main Menu ==============
static void draw_main_menu(VampireDeautherApp* app) {
    submenu_reset(app->submenu);
    
    submenu_add_item(app->submenu, "WiFi Deauther", 0, wifi_deauther_menu_callback, app);
    submenu_add_item(app->submenu, "BT Jammer", 1, bt_jammer_menu_callback, app);
    submenu_add_item(app->submenu, "Settings", 2, settings_menu_callback, app);
}
