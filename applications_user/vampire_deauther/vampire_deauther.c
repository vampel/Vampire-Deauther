#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include "views/view_main.h"

int32_t vampire_deauther_app(void* p) {
    UNUSED(p);

    // Crear dispatcher y obtener GUI
    ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
    Gui* gui = furi_record_open("gui");

    // Adjuntar dispatcher a GUI
    view_dispatcher_attach_to_gui(view_dispatcher, gui, ViewDispatcherTypeFullscreen);

    // Crear vista principal
    View* main_view = vampire_deauther_view_get();
    view_dispatcher_add_view(view_dispatcher, 0, main_view);
    view_dispatcher_switch_to_view(view_dispatcher, 0);

    // Ejecutar la vista
    view_dispatcher_run(view_dispatcher);

    // Limpiar
    view_dispatcher_remove_view(view_dispatcher, 0);
    view_free(main_view);
    view_dispatcher_free(view_dispatcher);
    furi_record_close("gui");

    return 0;
}
