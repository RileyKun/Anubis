#include "hl_client.hpp"

#include "link.hpp"

ClientClass* c_hl_client::get_all_classes(void) {
  return memory::find_vfunc<ClientClass*(__thiscall*)(void*)>(this, 8u)(this);
}