/* applications_user/vampire_deauther/vampire_deauther.h */
#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/variable_item_list.h>
#include <notification/notification.h>

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    VariableItemList* var_item_list;
    VariableItem* channel_item;
    NotificationApp* notifications;
    FuriHalUartId uart;
    uint8_t channel_index;
} VampireDeautherApp;
