#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/widget.h>
#include <notification/notification.h>

typedef struct {
    Gui* gui;
    NotificationApp* notifications;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* attack_view;
    FuriHalSerialHandle* serial_handle;
    bool attack_active;
} VampireDeautherApp;

int32_t vampire_deauther_app(void* p);