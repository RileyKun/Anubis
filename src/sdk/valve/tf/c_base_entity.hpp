#pragma once

#include "../client_entity.hpp"
#include "../netvars/netvars.hpp"

class c_base_entity : public i_client_entity {
  bool in_local_team(void);
  int  get_health(void);
  int  get_max_health(void);

  netvar(origin, vec3, "CBaseEntity", "m_vecOrigin");
  netvar(mins, vec3, "CBaseEntity", "m_vecMins");
  netvar(maxs, vec3, "CBaseEntity", "m_vecMaxs");
  netvar(team, int, "CBaseEntity", "m_iTeamNum");
};