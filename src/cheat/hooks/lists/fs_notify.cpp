#include "../hooks.hpp"

#include "link.hpp"

#include <safetyhook.hpp>

SafetyHookInline fs{};

// i also blame clang-format for this
void             hooks::fs_notify::startup() {
  fs = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.hl_client, 35), hooked_fs_notify);
}

void hooks::fs_notify::shutdown() {
  fs = {};
}

void __fastcall hooks::fs_notify::hooked_fs_notify(void* ecx, void* edx, frame_stage stage) {
  fs.thiscall<void>(ecx, stage);
  switch(stage) {
    case FRAME_RENDER_START:
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
      break;
  }
}