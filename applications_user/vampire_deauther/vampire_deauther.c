#include "views/view_main.h"
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <furi.h>

void vampire_deauther_app(void* p) {
    UNUSED(p);
    ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
    View* view = vampire_deauther_view_get();

    view_dispatcher_add_view(view_dispatcher, 0, view);
    view_dispatcher_attach_to_gui(
        view_dispatcher, gui_get_instance(), ViewDispatcherTypeFullscreen);
    view_dispatcher_run(view_dispatcher);

    view_dispatcher_remove_view(view_dispatcher, 0);
    view_free(view);
    view_dispatcher_free(view_dispatcher);
}
