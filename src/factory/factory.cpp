#include "factory.hpp"

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

  } else {
  }
}

void c_factory::interfaces() {
  // TODO: add assertions
  g_tf2.hl_client = memory::find_interface<c_hl_client*>("client.dll", "VClient017");
  g_tf2.engine_client = memory::find_interface<c_engine_client*>("engine.dll", "VEngineClient013");
  g_tf2.surface = memory::find_interface<i_surface*>("vguimatsurface.dll", "VGUI_Surface030");
}