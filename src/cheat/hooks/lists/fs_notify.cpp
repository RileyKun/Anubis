#include "../hooks.hpp"

#include "link.hpp"
#include <safetyhook.hpp>

#include "../../gui/gui.hpp"

#include "visuals/visuals.hpp"

SafetyHookInline fs{};

void             hooks::fs_notify::startup() {
  fs = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.hl_client, 35), hooked_fs_notify);
}

void hooks::fs_notify::shutdown() {
  fs = {};
}

void __fastcall hooks::fs_notify::hooked_fs_notify(void* ecx, void* edx, frame_stage stage) {
  fs.thiscall<void>(ecx, stage);
  switch(stage) {
    case FRAME_RENDER_START: {
      if(!ctx->screen_width || !ctx->screen_height) // drawsystem hasn't initialized, don't bother
        break;

      ctx->get_render_state();
      g_tf2.update_w2s();

      if(g_tf2.engine_client->is_connected()) {

        if(ctx->local_player) {
          f::esp.run();
        }

      }

      gui::watermark->paint();

      g_draw_threaded.flush();
      break;
    }
    case FRAME_RENDER_END:
    case FRAME_NET_UPDATE_START:
    case FRAME_NET_UPDATE_END:
    case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
      break;
    case FRAME_NET_UPDATE_POSTDATAUPDATE_END: {
      ctx->get_local();
      break;
    }
    case FRAME_START:
    case FRAME_UNDEFINED:
      break;
  }
}