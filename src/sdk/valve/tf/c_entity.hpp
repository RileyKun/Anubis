#pragma once

#include "../constants.hpp"
#include "../netvars/netvars.hpp"
#include "../hl_client.hpp"

#include "shared/memory.hpp"

class c_entity {
public:
  netvar(is_dead, bool, "DT_BasePlayer", "deadflag");
  netvar(flags, int, "DT_BasePlayer", "m_fFlags");
  netvar(mins, vec3, "DT_BaseEntity", "m_vecMins");
  netvar(maxs, vec3, "DT_BaseEntity", "m_vecMaxs");
  netvar(origin, vec3, "DT_BaseEntity", "m_vecOrigin");

  // game virtual functions
  bool is_dormant(void);
  ClientClass* get_class(void);
  matrix3x4& world_transform(void);

  // cheat functions
  bool is_player();
  bool is_building();
  bool is_friend();
  vec3 central_position();

  bool calc_bounding_box(rect_t& output) noexcept;

};

// NOTE: Riley; ONLY USE THIS IF YOU ARE CERTAIN THE CONTEXT WILL ALWAYS BE C_TFPLAYER
// OTHERWISE, USE C_ENTITY.
using c_player = c_entity;