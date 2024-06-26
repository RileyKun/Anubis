#include "movement.hpp"

#include "../config.hpp"

void c_movement::bunnyhop(c_player* player, c_user_cmd* cmd) {
  if(!settings::movement::bunny_hop)
    return;

  int         flags = player->flags();
  int&        buttons = cmd->buttons;
  static bool jump_state = false;

  if(buttons & IN_JUMP) {
    if(!jump_state && !(flags & FL_ONGROUND))
      buttons &= ~IN_JUMP;

    else if(jump_state)
      jump_state = false;
  }

  else if(!jump_state)
    jump_state = true;
}

void c_movement::run(c_user_cmd* cmd) {
  if(ctx->local_player->is_dead())
    return;

  bunnyhop(ctx->local_player, cmd);
}
