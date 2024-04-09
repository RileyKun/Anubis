#include "hl_client.hpp"

#include "link.hpp"

ClientClass* c_hl_client::get_all_classes(void) {
  return memory::find_vfunc<ClientClass*(__thiscall*)(void*)>(this, 8u)(this);
}

bool c_hl_client::get_player_view(c_view_setup& player_view) {
  return memory::find_vfunc<bool(__thiscall*)(void*, c_view_setup&)>(this, 59u)(this, player_view);
}