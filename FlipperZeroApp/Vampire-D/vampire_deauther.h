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
#define DEAUTH_PACKET_SIZE 26
#define MAX_NETWORKS 50

typedef enum {
    VampireDeautherViewSubmenu,
    VampireDeautherViewAttack,
    VampireDeautherViewScan,
    VampireDeautherViewSettings
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
    Widget* attack_view;
    VariableItemList* settings_view;
    
    FuriHalSerialHandle* serial_handle;
    FuriThread* serial_thread;
    FuriStreamBuffer* rx_stream;
    
    bool attack_active;
    bool scan_active;
    WiFiNetwork* current_target;
    WiFiNetwork networks[MAX_NETWORKS];
    uint8_t network_count;
    
    // Estado de la aplicación
    uint32_t current_channel;
    bool scanning_5ghz;
} VampireDeautherApp;

// Prototipos de funciones principales
int32_t vampire_deauther_app(void* p);

// Funciones de serial
void serial_worker_init(VampireDeautherApp* app);
void serial_worker_free(VampireDeautherApp* app);
void send_serial_command(VampireDeautherApp* app, const char* command);

// Funciones de WiFi
void start_scan(VampireDeautherApp* app);
void stop_scan(VampireDeautherApp* app);
void start_deauth(VampireDeautherApp* app, uint8_t network_index);
void stop_attack(VampireDeautherApp* app);

// Callbacks
void submenu_callback(void* context, uint32_t index);
void serial_rx_callback(uint8_t* buf, size_t len, void* context);
