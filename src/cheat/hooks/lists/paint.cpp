#include "../hooks.hpp"
#include "link.hpp"

#include <safetyhook.hpp>

#include <mutex>

// includes from features
#include "../../gui/gui.hpp"

SafetyHookInline pt{};
SafetyHookInline size_change{};

std::once_flag   init;

void             hooks::paint::startup() {
  g_draw->reload_fonts();
  pt = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.engine_vgui, 14), hooked_paint);
  size_change =
      safetyhook::create_inline(memory::vfunc_ptr(g_tf2.surface, 111), hooked_size_changed);
}

void hooks::paint::shutdown() {
  pt = {};
  size_change = {};
}

void __fastcall hooks::paint::hooked_paint(void* ecx, void* edx, mode_t mode) {
  pt.thiscall<void>(ecx, mode);
  std::call_once(init, [&] {
    g_tf2.engine_client->get_screen_size(ctx->screen_width, ctx->screen_height);
  });

  if(mode & mode_t::PAINT_UIPANELS) {
    g_tf2.surface->start();
    {
      gui::watermark->paint();
    }
    g_tf2.surface->stop();
  }
}

void __fastcall hooks::paint::hooked_size_changed(void* ecx, void* edx, int old_width,
                                                  int old_height) {
  size_change.thiscall<void>(ecx, old_width, old_height);
  g_tf2.engine_client->get_screen_size(ctx->screen_width, ctx->screen_height);
  g_draw->reload_fonts();
}