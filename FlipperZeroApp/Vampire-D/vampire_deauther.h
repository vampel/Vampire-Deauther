#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/widget.h>
#include <gui/modules/variable_item_list.h>
#include <notification/notification.h>
#include <furi_hal_serial.h>

#define TAG "VampireDeauther"
#define SERIAL_BAUDRATE 115200
#define MAX_NETWORKS 50

typedef enum {
    VampireDeautherViewSubmenu,
    VampireDeautherViewScan,
    VampireDeautherViewAttack,
    VampireDeautherViewSettings,
    VampireDeautherViewAbout
} VampireDeautherView;

typedef struct {
    uint8_t bssid[6];
    char ssid[33];
    int8_t rssi;
    uint8_t channel;
    bool is_5ghz;
} WiFiNetwork;

typedef struct {
    Gui* gui;
    NotificationApp* notifications;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* scan_view;
    Widget* attack_view;
    VariableItemList* settings_view;
    Widget* about_view;
    
    FuriHalSerialHandle* serial_handle;
    FuriThread* serial_thread;
    FuriStreamBuffer* rx_stream;
    
    bool attack_active;
    bool scan_active;
    WiFiNetwork* current_target;
    WiFiNetwork networks[MAX_NETWORKS];
    uint8_t network_count;
    
    // Configuración
    bool enable_5ghz;
    uint8_t attack_type;
} VampireDeautherApp;
