#include "../hooks.hpp"
#include "link.hpp"

#include <safetyhook.hpp>

SafetyHookInline c_move{};

// i blame clang format for this right here
void             hooks::createmove::startup() {
  c_move = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.client_mode, 21), hooked_createmove);
}

void hooks::createmove::shutdown() {
  c_move = {};
}

bool __fastcall hooks::createmove::hooked_createmove(void* ecx, void* edx, float sample_time,
                                                     c_user_cmd* cmd) {
  auto result = c_move.thiscall<bool>(ecx, sample_time, cmd);

  // prevent createmove from running every frame
  if(!cmd->command_number)
    return result;

  // TODO: set viewangles
  uintptr_t _bp;
  __asm mov _bp, ebp;
  bool*     b_send_packet = reinterpret_cast<bool*>(***reinterpret_cast<uintptr_t***>(_bp) - 0x1);
  
  // this will prevent our actual local angles being overridden by c_user_cmd
  return false;
}