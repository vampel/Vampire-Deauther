#include <furi.h>
#include <gui/gui.h>
#include "views/view_main.h"

void vampire_deauther_app(void* p) {
    UNUSED(p);

    Gui* gui = furi_record_open(RECORD_GUI);
    ViewPort* view_port = view_port_alloc();

    view_port_draw_callback_set(view_port, render_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, NULL);

    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    while(view_port_is_enabled(view_port)) {
        furi_delay_ms(100);
    }

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
}
