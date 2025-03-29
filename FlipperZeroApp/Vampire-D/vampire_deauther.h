#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <notification/notification_messages.h>

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    NotificationApp* notifications;
} VampireDeautherApp;

typedef enum {
    VampireDeautherViewSubmenu,
} VampireDeautherView;
