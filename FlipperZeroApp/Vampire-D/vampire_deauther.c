#include "vampire_deauther.h"

static void submenu_callback(void* context, uint32_t index) {
    VampireDeautherApp* app = context;
    switch(index) {
        case 0:
            // Scan WiFi
            break;
        case 1:
            // Deauth Attack
            break;
        case 2:
            // Beacon Spam
            break;
        case 3:
            // Settings
            break;
    }
}

static void vampire_deauther_app_init(VampireDeautherApp* app) {
    app->view_dispatcher = view_dispatcher_alloc();
    app->submenu = submenu_alloc();
    
    // Configure submenu
    submenu_add_item(app->submenu, "Scan WiFi", 0, submenu_callback, app);
    submenu_add_item(app->submenu, "Deauth Attack", 1, submenu_callback, app);
    submenu_add_item(app->submenu, "Beacon Spam", 2, submenu_callback, app);
    submenu_add_item(app->submenu, "Settings", 3, submenu_callback, app);
    
    view_dispatcher_add_view(app->view_dispatcher, 
                           VampireDeautherViewSubmenu, 
                           submenu_get_view(app->submenu));
    view_dispatcher_switch_to_view(app->view_dispatcher, 
                                 VampireDeautherViewSubmenu);
}

int32_t vampire_deauther_app(void* p) {
    VampireDeautherApp* app = malloc(sizeof(VampireDeautherApp));
    vampire_deauther_app_init(app);
    
    view_dispatcher_run(app->view_dispatcher);
    
    submenu_free(app->submenu);
    view_dispatcher_free(app->view_dispatcher);
    free(app);
    
    return 0;
}
