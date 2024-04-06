#include "engine_vgui.hpp"

#include "link.hpp"

v_panel c_engine_vgui::get_panel(panel_t type) {
  return memory::find_vfunc<v_panel(__thiscall*)(void*, panel_t)>(this, 1u)(this, type);
}
bool c_engine_vgui::is_game_ui_visible(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 21u)(this);
}
