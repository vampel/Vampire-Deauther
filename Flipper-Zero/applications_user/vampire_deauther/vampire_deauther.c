// vampire_deauther.c
#include "vampire_deauther.h"

/* Estructura de Menú Principal */
static void draw_main_menu(VampireDeautherApp* app) {
    submenu_reset(app->submenu);
    
    // Menú WiFi Deauther
    submenu_add_item(
        app->submenu,
        "WiFi Deauther",
        0,
        wifi_deauther_menu_callback,
        app);
    
    // Menú BT Jammer
    submenu_add_item(
        app->submenu,
        "BT Jammer",
        1,
        bt_jammer_menu_callback,
        app);
}

/* Submenú WiFi Deauther */
static void wifi_deauther_menu_callback(void* context) {
    VampireDeautherApp* app = context;
    submenu_reset(app->submenu);
    
    submenu_add_item(
        app->submenu,
        "WiFi All Deauth",
        0,
        wifi_all_deauth_callback,
        app);
        
    submenu_add_item(
        app->submenu,
        "WiFi 2.4GHz Deauth",
        1,
        wifi_24ghz_deauth_callback,
        app);
        
    submenu_add_item(
        app->submenu,
        "WiFi 5GHz Deauth",
        2,
        wifi_5ghz_deauth_callback,
        app);
}

/* Submenú BT Jammer */
static void bt_jammer_menu_callback(void* context) {
    VampireDeautherApp* app = context;
    submenu_reset(app->submenu);
    
    submenu_add_item(
        app->submenu,
        "BT Jammer All",
        0,
        bt_jammer_all_callback,
        app);
        
    submenu_add_item(
        app->submenu,
        "BT Jammer Classic",
        1,
        bt_jammer_classic_callback,
        app);
        
    submenu_add_item(
        app->submenu,
        "BT Jammer BLE",
        2,
        bt_jammer_ble_callback,
        app);
}

/* Callbacks para WiFi */
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

/* Callbacks para BT Jammer */
static void bt_jammer_all_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_ALL\n", 11);
    notification_message(app->notifications, &sequence_blink_magenta_100);
}

static void bt_jammer_classic_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_CLASSIC\n", 15);
    notification_message(app->notifications, &sequence_blink_cyan_100);
}

static void bt_jammer_ble_callback(void* context) {
    VampireDeautherApp* app = context;
    furi_hal_uart_tx(app->uart, "BT_JAM_BLE\n", 11);
    notification_message(app->notifications, &sequence_blink_yellow_100);
}
