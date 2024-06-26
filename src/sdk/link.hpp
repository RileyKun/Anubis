#pragma once

// include sdk headers
#include "valve/client_entity.hpp"
#include "valve/client_entity_list.hpp"
#include "valve/client_mode.hpp"
#include "valve/engine_client.hpp"
#include "valve/engine_vgui.hpp"
#include "valve/hl_client.hpp"
#include "valve/render_view.hpp"
#include "valve/surface.hpp"
#include "valve/user_cmd.hpp"

// Team Fortress sdk headers
#include "valve/tf/c_entity.hpp"

// include cheat headers
#include "shared/console/console.hpp"
#include "shared/drawsystem/drawsystem.hpp"
#include "shared/memory.hpp"

// NOTE: Riley; For anyone reading this, a cleanup of i_client_ent* needs to be done.
// While ripping interfaces straight out of the game would make things easier. I would like
// Anubis to leave a smaller footprint in code size.
class c_tf2 {
public:
  // store all interfaces of the game
  c_engine_client*      engine_client = nullptr;
  c_hl_client*          hl_client = nullptr;
  c_engine_vgui*        engine_vgui = nullptr;
  i_surface*            surface = nullptr;
  i_client_mode_shared* client_mode = nullptr;
  i_client_entity_list* entity_list = nullptr;
  iv_render_view*       render_view = nullptr;

  bool                  w2s(const vec3& origin, vec2& project);
};

class c_ctx {
public:
  c_player*   local_player = nullptr;

  int         screen_width = 0;
  int         screen_height = 0;

  bool        has_spawned_once = false;

  matrix4x4 matrix = {};

  void        get_local();
  // returns true if we should do an optimized render
  bool        get_render_state();
  void        set_render_state(bool state);

private:
  bool do_optimized_render = false;
};

inline auto  ctx = std::make_unique<c_ctx>();
inline c_tf2 g_tf2{};
inline auto  g_console = std::make_unique<c_console>();
inline auto  drawsystem = std::make_unique<c_drawsystem>();
inline auto  g_draw = std::make_unique<c_render>(); // <- because that could confuse people
inline c_render_threaded g_draw_threaded{}; // <- NOTE: Riley; this should probably get renamed