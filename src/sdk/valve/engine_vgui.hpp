#pragma once

enum class panel_t : int {
  PANEL_ROOT = 0,
  PANEL_GAMEUIDLL,
  PANEL_CLIENTDLL,
  PANEL_TOOLS,
  PANEL_INGAMESCREENS,
  PANEL_GAMEDLL,
  PANEL_CLIENTDLL_TOOLS
};

using v_panel = unsigned int;

class c_engine_vgui {
public:
  v_panel get_panel(panel_t type);
  // returns true if the pause menu is active
  bool    is_game_ui_visible(void);
};