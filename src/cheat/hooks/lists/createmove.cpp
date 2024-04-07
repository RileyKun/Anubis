#include "../hooks.hpp"
#include "link.hpp"

#include <safetyhook.hpp>

#include "movement/movement.hpp"

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

  if(result) {
    g_tf2.engine_client->set_view_angles(cmd->view_angles);
  }
  
  auto bp = reinterpret_cast<uintptr_t>(_AddressOfReturnAddress()) - sizeof(void*);
  bool& b_send_packet = *reinterpret_cast<bool*>(***reinterpret_cast<uintptr_t***>(bp) - 0x1);
  
  if(ctx->local_player) {
    f::movement.run(cmd);
  }
  // this will prevent our actual local angles being overridden by c_user_cmd
  return false;
}