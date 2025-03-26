#include <furi.h>
#include <gui/gui.h>

// Menú principal
static void draw_menu(Canvas* canvas) {
    canvas_draw_str(canvas, 10, 20, "Vampire-Deauther");
    canvas_draw_frame(canvas, 5, 30, 118, 30);

    // Ítems del menú
    const char* items[] = {"WiFi 2.4GHz", "WiFi 5GHz", "BT Jammer"};
    for(uint8_t i = 0; i < 3; i++) {
        canvas_draw_str(canvas, 15, 50 + (i * 10), items[i]);
    }
}

// Pantalla de ataque
static void draw_attack(Canvas* canvas, uint8_t channel) {
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Atacando canal: %d", channel);
    canvas_draw_str(canvas, 10, 30, buffer);
}

// Handler de la UI
void ui_draw_callback(Canvas* canvas, void* ctx) {
    if(ctx == 0) draw_menu(canvas);
    else draw_attack(canvas, (uint8_t)ctx);
}
