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

// credits: JAGNEmk
bool c_tf2::w2s(const vec3& origin, vec3& project) {
  const matrix3x4& w2s = ctx->matrix.as_3x4();

  float w = w2s[3][0] * origin[0] + w2s[3][1] * origin[1] + w2s[3][2] * origin[2] + w2s[3][3];

  if(w > 0.001f) {
    auto width = static_cast<float>(ctx->screen_width);
    auto height = static_cast<float>(ctx->screen_height);
    float dbw = 1.0f / w;

    project.x =
        (width / 2.0f) +
        (0.5f *
             ((w2s[0][0] * origin[0] + w2s[0][1] * origin[1] + w2s[0][2] * origin[2] + w2s[0][3]) *
              dbw) *
             width +
         0.5f);
    project.y =
        (height / 2.0f) -
        (0.5f *
             ((w2s[1][0] * origin[0] + w2s[1][1] * origin[1] + w2s[1][2] * origin[2] + w2s[1][3]) *
              dbw) *
             height +
         0.5f);

    return true;
  }
  return false;
}

void c_tf2::update_w2s() {
  c_view_setup view_setup{};

  if(g_tf2.hl_client->get_player_view(view_setup)) {
    v_matrix w2v{};
    v_matrix w2p{};
    v_matrix w2px{};

    g_tf2.render_view->get_matrices_for_view(view_setup, &w2v, &w2p, &ctx->matrix, &w2px);
  }
}
