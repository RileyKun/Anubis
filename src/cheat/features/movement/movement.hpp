#pragma once

class c_user_cmd;
class c_tf_player;

class c_movement {
private:
  void bunnyhop(c_tf_player* player, c_user_cmd* cmd);

public:
  void run(c_user_cmd* cmd);
};

namespace f {
inline c_movement movement;
}