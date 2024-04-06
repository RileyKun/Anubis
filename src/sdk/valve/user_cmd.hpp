#pragma once

#include "constants.hpp"
#include "mathlib.hpp"

class c_user_cmd {
public:
  virtual ~c_user_cmd(){};

  int       command_number;
  int       tick_count;
  QAngle    view_angles;
  float     forward_move;
  float     side_move;
  float     up_move;
  int       buttons;
  std::byte impulse;
  int       weapon_select;
  int       weapon_subtype;
  int       random_seed;
  short     mouse_dx;
  short     mouse_dy;
};