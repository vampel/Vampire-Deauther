#include "menu_view.h"
int32_t vampire_deauther_app(void* p) {
  ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(view_dispatcher, gui, ViewDispatcherTypeFullscreen);
  view_dispatcher_add_view(view_dispatcher, MenuView, menu_view_alloc());
  view_dispatcher_switch_to_view(view_dispatcher, MenuView);
  view_dispatcher_run(view_dispatcher);
  return 0;
}
