#pragma once

#include <gui/view.h>
#include <gui/canvas.h>
#include <gui/view_port.h>
#include <input/input.h>

void render_callback(Canvas* canvas, void* context);
bool input_callback(InputEvent* event, void* context);
