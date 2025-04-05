#pragma once

#include <gui/canvas.h>
#include <gui/view_dispatcher.h>
#include <gui/view.h>
#include <input/input.h>

View* vampire_deauther_view_get(void);
void render_callback(Canvas* canvas, void* context);
void input_callback(InputEvent* event, void* context);
