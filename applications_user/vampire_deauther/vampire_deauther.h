#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <furi_hal_serial.h>
#include <furi_hal_gpio.h>
#include "bw16_commands.h"

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    View* main_view;
    FuriHalSerialHandle* serial_handle;
    bool bw16_ready;
} VampireDeautherApp;

void bw16_init_serial(VampireDeautherApp* app);
bool bw16_send_command(VampireDeautherApp* app, const char* command);