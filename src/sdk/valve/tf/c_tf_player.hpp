#pragma once

#include "../constants.hpp"
#include "../netvars/netvars.hpp"

class c_tf_player {
public:
  netvar(is_dead, bool, "DT_BasePlayer", "deadflag");
  netvar(flags, int, "DT_BasePlayer", "m_fFlags");
};