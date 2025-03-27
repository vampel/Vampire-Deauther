#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <notification/notification.h>
#include <furi_hal_uart.h>

typedef struct {
    Gui* gui;
    NotificationApp* notifications;
    Submenu* submenu;
    FuriHalUartId uart;
} VampireDeautherApp;

VampireDeautherApp* vampire_deauther_app_alloc();
void vampire_deauther_app_free(VampireDeautherApp* app);
