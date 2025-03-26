static void menu_view_draw_callback(Canvas* canvas, void* ctx) {
  canvas_draw_str(canvas, 10, 20, "Vampire-Deauther");
  canvas_draw_icon(canvas, 10, 30, &I_wifi_24ghz_10px);
  canvas_draw_str(canvas, 30, 40, "2.4GHz Deauth");
  // ... (opciones restantes)
}
