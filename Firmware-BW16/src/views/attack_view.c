static void attack_view_draw_callback(Canvas* canvas, void* ctx) {
  canvas_draw_icon(canvas, 0, 0, &I_wifi_24ghz_10px);
  canvas_draw_str(canvas, 30, 10, "Atacando 2.4GHz");
  canvas_draw_str(canvas, 30, 30, "Canal: %d", current_channel);
}
