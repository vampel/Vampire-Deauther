flipper_app(
    NAME "vampire_deauther"
    STACK_SIZE 4096
    ENTRY_POINT vampire_deauther_app
    SOURCES
        vampire_deauther.c
        views/view_main.c
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/views
    LIBRARIES
        furi
        gui
        furi_hal
)
