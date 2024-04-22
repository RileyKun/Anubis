#pragma once

#include "../constants.hpp"
#include "../netvars/netvars.hpp"
#include "../hl_client.hpp"
#include "../client_entity.hpp"

#include "shared/memory.hpp"

class c_entity : public i_client_entity {
public:
  netvar(is_dead, bool, "DT_BasePlayer", "deadflag");
  netvar(flags, int, "DT_BasePlayer", "m_fFlags");
  netvar(mins, vec3, "DT_BaseEntity", "m_vecMins");
  netvar(maxs, vec3, "DT_BaseEntity", "m_vecMaxs");
  netvar(origin, vec3, "DT_BaseEntity", "m_vecOrigin");
  netvar(health, int, "DT_BasePlayer", "m_iHealth");
  netvar(max_health, int, "DT_BasePlayer", "m_iMaxHealth");
};

// NOTE: Riley; ONLY USE THIS IF YOU ARE CERTAIN THE CONTEXT WILL ALWAYS BE C_TFPLAYER
// OTHERWISE, USE C_ENTITY.
using c_player = c_entity;