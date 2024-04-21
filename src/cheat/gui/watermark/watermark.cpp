#include "watermark.hpp"

#include "link.hpp"

void c_watermark::paint() {
  g_draw_threaded.string(nullptr, 8, ctx->screen_height * 0.06, true, e_text_align::TEXT_LEFT,
                         ImColor(1.f, 1.f, 1.f, 1.f), "Anubis [early alpha]");

  if(g_tf2.engine_client->is_in_game())
    return;
#ifdef _DEBUG
  g_draw_threaded.string(nullptr, 10, ctx->screen_height - 20, true, e_text_align::TEXT_LEFT,
                         ImColor(1.f, 0.f, 0.f, 0.35f), "Developer build.");
#else
  g_draw_threaded.string(nullptr, 8, ctx->screen_height - 20, true, e_text_align::TEXT_LEFT,
                         ImColor(1.f, 1.f, 1.f, 0.35f), "Compiled on: " __DATE__);
#endif // _DEBUG
}
