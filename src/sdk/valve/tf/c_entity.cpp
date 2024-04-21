#include "c_entity.hpp"
#include "link.hpp"

#include <array>

bool c_entity::is_player() {
  /*if(auto client_class = get_class()) {
    // NOTE: Riley; C-Style casts make this more readable, do not change them if you are making
    // a pull request.
    // TODO: fix this, this should not be this way.
    return client_class->m_ClassID == 246;
  } else*/
    return false;
}
bool c_entity::is_building() {
  /*if(auto client_class = get_class()) {
    // NOTE: Riley; C-Style casts make this more readable, do not change them if you are making
    // a pull request.
    return client_class->m_ClassID == (int)e_class_ids::CObjectSentrygun ||
           client_class->m_ClassID == (int)e_class_ids::CObjectDispenser ||
           client_class->m_ClassID == (int)e_class_ids::CObjectTeleporter;
  } else*/
    return false;
}

// TODO: implement this function.
bool c_entity::is_friend() {
  return false;
}

// NOTE: this function is deprecated and will be removed at a later date.
bool c_entity::calc_bounding_box(rect_t& output) noexcept {
  return false;
}

vec3 c_entity::central_position() {
  return origin() + vec3_t(0.0f, 0.0f, (mins().z + maxs().z) * 0.5f);
}