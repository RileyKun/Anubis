#include "watermark.hpp"

#include "link.hpp"

void c_watermark::draw_build_info() {
#ifdef _DEBUG
  g_draw->string(g_draw->fonts[FONT_WATERMARK], 5, ctx->screen_height - 20, color(255, 0, 0, 128),
                 e_text_align::TXT_LEFT, "Developer build.");
#else
  g_draw->string(g_draw->fonts[FONT_WATERMARK], 7, ctx->screen_height - 22,
                 color(255, 255, 255, 128), e_text_align::TXT_LEFT, "Compiled: " __DATE__);
#endif
}
void c_watermark::draw_cheat_info() {
  g_draw->string(g_draw->fonts[FONT_WATERMARK], 10, ctx->screen_height * 0.05,
                 color(255, 255, 255, 255), e_text_align::TXT_LEFT, "Anubis [early alpha]");
}
void c_watermark::paint() {
  if(!g_tf2.engine_client->is_in_game()) {
    draw_build_info();
  }
  draw_cheat_info();
}
