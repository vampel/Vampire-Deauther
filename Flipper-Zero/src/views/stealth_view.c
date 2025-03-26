static void stealth_view_draw_callback(Canvas* canvas, void* ctx) {
    canvas_draw_str(canvas, 10, 20, "MODO STEALTH");
    canvas_draw_icon(canvas, 30, 30, &I_stealth_icon);
    canvas_draw_str(canvas, 60, 40, "ACTIVO");
    
    // Muestra MAC aleatoria actual
    canvas_draw_str(canvas, 10, 60, "MAC:");
    canvas_draw_str(canvas, 40, 60, get_current_mac());
}
