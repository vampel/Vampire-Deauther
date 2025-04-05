#pragma once

#include <gui/gui.h>
#include <gui/view.h>
#include <furi_hal_serial.h>
#include "../bw16_commands.h"

typedef struct {
    size_t selected_index;
    bool scanning;
    bool attacking;
    uint8_t ap_count;
    uint8_t sta_count;
} VampireDeautherModel;

bool input_callback(InputEvent* event, void* context);
void render_callback(Canvas* canvas, void* context);
View* vampire_deauther_view_get(void);