#include "c_base_entity.hpp"

#include "link.hpp"

bool c_base_entity::in_local_team(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 67u)(this);
}
int c_base_entity::get_health(void) {
  return memory::find_vfunc<int(__thiscall*)(void*)>(this, 95u)(this);
}
int c_base_entity::get_max_health(void) {
  return memory::find_vfunc<int(__thiscall*)(void*)>(this, 96u)(this);
}
