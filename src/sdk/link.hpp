#pragma once

// include sdk headers
#include "valve/client_mode.hpp"
#include "valve/engine_client.hpp"
#include "valve/engine_vgui.hpp"
#include "valve/hl_client.hpp"
#include "valve/surface.hpp"
#include "valve/user_cmd.hpp"

// include cheat headers
#include "shared/ctx.hpp"
#include "shared/memory.hpp"

// store all interfaces of the game
class c_tf2 {
public:
  c_engine_client*      engine_client = nullptr;
  c_hl_client*          hl_client = nullptr;
  c_engine_vgui*        engine_vgui = nullptr;
  i_surface*            surface = nullptr;
  i_client_mode_shared* client_mode = nullptr;
};

inline c_tf2 g_tf2{};