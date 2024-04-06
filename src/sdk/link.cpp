#include "link.hpp"

// cleans up frame_stage_notify
void c_ctx::get_local() {
  g_tf2.entity_list->get_client_entity(g_tf2.engine_client->get_local_player())->as<c_tf_player>();
}
