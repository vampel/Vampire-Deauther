#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <notification/notification.h>

#define MAX_APS 3  // Reducido para Momentum

typedef struct {
    uint8_t bssid[6];
    char ssid[33];
    uint8_t channel;
} AccessPoint;

typedef struct {
    // Componentes GUI
    Gui* gui;
    ViewPort* view_port;
    
    // Comunicación serial
    FuriHalSerialHandle* serial_handle;
    
    // Datos
    AccessPoint access_points[MAX_APS];
    uint8_t ap_count;
} VampireDeautherApp;

int32_t vampire_deauther_app(void* p);