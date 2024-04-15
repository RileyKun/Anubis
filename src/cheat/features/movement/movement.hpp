#pragma once

#include "link.hpp"

class c_movement {
private:
  void bunnyhop(c_player* player, c_user_cmd* cmd);

public:
  void run(c_user_cmd* cmd);
};

namespace f {
inline c_movement movement;
}