#include "link.hpp"

// cleans up frame_stage_notify
void c_ctx::get_local() {
  local_player = g_tf2.entity_list->get_client_entity(g_tf2.engine_client->get_local_player())
                     ->as<c_player>();
}
// credits: JAGNEmk
bool c_tf2::w2s(const vec3& origin, vec2& project) {
  // NOTE: Riley; Must be made const.
  const matrix3x4& matrix = ctx->matrix.as_3x4();

  float            width =
      matrix[3][0] * origin[0] + matrix[3][1] * origin[1] + matrix[3][2] * origin[2] + matrix[3][3];

  if(width > 0.001f) {
    float inverted = 1.f / width;
    project.x = (static_cast<float>(ctx->screen_width) * .5f) +
                (.5f *
                     ((matrix[0][0] * origin[0] + matrix[0][1] * origin[1] +
                       matrix[0][2] * origin[2] + matrix[0][3]) *
                      inverted) *
                     static_cast<float>(ctx->screen_width) +
                 .5f);
    project.y = (static_cast<float>(ctx->screen_height) * .5f) -
                (.5f *
                     ((matrix[1][0] * origin[0] + matrix[1][1] * origin[1] +
                       matrix[1][2] * origin[2] + matrix[1][3]) *
                      inverted) *
                     static_cast<float>(ctx->screen_height) +
                 .5f);
    return true;
  }
  return false;
}
