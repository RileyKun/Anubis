#include "link.hpp"

// cleans up frame_stage_notify
void c_ctx::get_local() {
  local_player =
      g_tf2.entity_list->get_client_entity(g_tf2.engine_client->get_local_player())->as<c_player>();
}

bool c_ctx::get_render_state() {
  return this->do_optimized_render;
}

void c_ctx::set_render_state(bool state) {
  this->do_optimized_render = state;
}

// credits: D3X - From his L4D2 cheat.
bool c_tf2::w2s(const vec3& origin, vec2& project) {
  const auto& matrix = g_tf2.engine_client->world_to_screen_matrix();
  const auto  w = glm::dot(matrix[3].xyz(), origin) + matrix[3].w;

  if(w <= 0.001f)
    return false;

  const vec2 clip_space(glm::dot(matrix[0].xyz(), origin) + matrix[0].w,
                        glm::dot(matrix[1].xyz(), origin) + matrix[1].w);

  const auto normalized_space = clip_space / w;

  project.x = (1.f + normalized_space.x) * ((float)ctx->screen_width / 2.f);
  project.y = (1.f + normalized_space.y) * ((float)ctx->screen_height / 2.f);
  return true;
}
