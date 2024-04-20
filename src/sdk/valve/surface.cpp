#include "surface.hpp"

#include "link.hpp"

void i_surface::set_cursor_visible(bool visible) {
  memory::find_vfunc<void(__thiscall*)(void*, bool)>(this, 52u)(this, visible);
}

bool i_surface::is_cursor_visible(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 53u)(this);
}

void i_surface::play_sound(const char* name) {
  memory::find_vfunc<void(__thiscall*)(void*, const char*)>(this, 78u)(this, name);
}