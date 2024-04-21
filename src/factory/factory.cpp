#include "factory.hpp"

#include "../cheat/hooks/hooks.hpp"
#include "link.hpp"

void c_factory::startup() {
  interfaces();
  hooks(true);
}

void c_factory::shutdown() {
  hooks(false);
}

void c_factory::hooks(bool startup) {
  if(startup) {
    hooks::createmove::startup();
    hooks::fs_notify::startup();
    hooks::directx::startup();
    hooks::paint::startup();
  } else {
    hooks::createmove::shutdown();
    hooks::fs_notify::shutdown();
    hooks::directx::shutdown();
    hooks::paint::startup();
  }
}

void c_factory::interfaces() {
  // TODO: add assertions
  g_tf2.hl_client = memory::find_interface<c_hl_client*>("client.dll", "VClient017");
  g_tf2.engine_client = memory::find_interface<c_engine_client*>("engine.dll", "VEngineClient013");
  g_tf2.surface = memory::find_interface<i_surface*>("vguimatsurface.dll", "VGUI_Surface030");
  g_tf2.client_mode = **memory::find_pattern<i_client_mode_shared***, 2u>("client.dll", "8B 0D ? ? ? ? FF 96 ? ? ? ? 8B 4D");
  g_tf2.engine_vgui = memory::find_interface<c_engine_vgui*>("engine.dll", "VEngineVGui002");
  g_tf2.entity_list =
      memory::find_interface<i_client_entity_list*>("client.dll", "VClientEntityList003");
  g_tf2.render_view = memory::find_interface<iv_render_view*>("engine.dll", "VEngineRenderView014");
}