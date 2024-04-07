#include "movement.hpp"

#include "link.hpp"

// FIXME: Riley; allow bunnyhopping as scout
void c_movement::bunnyhop(c_tf_player* player, c_user_cmd* cmd) {
  auto  flags = player->flags();
  auto& buttons = cmd->buttons;

  if(!!(buttons & IN_JUMP) && !(flags & FL_ONGROUND)) {
    buttons &= ~IN_JUMP;
  }
}

void c_movement::run(c_user_cmd* cmd) {
  if(ctx->local_player->is_dead())
    return;

  bunnyhop(ctx->local_player, cmd);
}
