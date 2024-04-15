#include "c_entity.hpp"
#include "link.hpp"

#include <array>

bool c_entity::is_dormant(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 8u)(this);
}

ClientClass* c_entity::get_class(void) {
  return memory::find_vfunc<ClientClass*(__thiscall*)(void*)>(this + 8, 2u)(this);
}

matrix3x4& c_entity::world_transform(void) {
  return memory::find_vfunc<matrix3x4&(__thiscall*)(void*)>(this + 4, 34u)(this);
}

bool c_entity::is_player() {
  if(auto client_class = get_class()) {
    // NOTE: Riley; C-Style casts make this more readable, do not change them if you are making
    // a pull request.
    // TODO: fix this, this should not be this way.
    return client_class->m_ClassID == (int)e_class_ids::CTFPlayer;
  } else
    return false;
}
bool c_entity::is_building() {
  if(auto client_class = get_class()) {
    // NOTE: Riley; C-Style casts make this more readable, do not change them if you are making
    // a pull request.
    return client_class->m_ClassID == (int)e_class_ids::CObjectSentrygun ||
           client_class->m_ClassID == (int)e_class_ids::CObjectDispenser ||
           client_class->m_ClassID == (int)e_class_ids::CObjectTeleporter;
  } else
    return false;
}

// TODO: implement this function.
bool c_entity::is_friend() {
  return false;
}

// TODO: move this to esp
bool c_entity::calc_bounding_box(rect_t& output) noexcept {
  // get mins and maxes of the entity
  const auto&         vec_mins = mins();
  const auto&         vec_maxs = maxs();

  // get our world transform
  const matrix3x4&    matrix = world_transform();

  // now generate an array of points
  std::array<vec3, 8> points = {
      vec3(vec_mins.x, vec_mins.y, vec_mins.z), vec3(vec_mins.x, vec_maxs.y, vec_mins.z),
      vec3(vec_maxs.x, vec_maxs.y, vec_mins.z), vec3(vec_maxs.x, vec_mins.y, vec_mins.z),
      vec3(vec_maxs.x, vec_maxs.y, vec_maxs.z), vec3(vec_mins.x, vec_maxs.y, vec_maxs.z),
      vec3(vec_mins.x, vec_mins.y, vec_maxs.z), vec3(vec_maxs.x, vec_mins.y, vec_maxs.z)};

  auto                left = std::numeric_limits<float>::max();
  auto                top = std::numeric_limits<float>::max();
  auto                right = std::numeric_limits<float>::lowest();
  auto                bottom = std::numeric_limits<float>::lowest();

  // now generate our screenspace points
  std::array<vec2, 8> screen;

  // iterate through the array and place out points on the screen
  for(std::size_t i = 0; i < 8; ++i) {
    if(!c_tf2::w2s(points[i].transform(matrix), screen[i]))
      return {};

    left = std::min(left, screen[i].x);
    top = std::min(top, screen[i].y);
    right = std::max(right, screen[i].x);
    bottom = std::max(bottom, screen[i].y);
  }

  // are these really needed?
  auto x = left;
  auto y = top;

  auto width = right - left;
  auto height = bottom - top;

  if(is_player()) {
    x += ((right - left) / 8.f);
    width -= (((right - left) / 8.f) * 2.f);
  }

  // we've finished, output the bbox
  output = {
      static_cast<int>(x),
      static_cast<int>(y),
      static_cast<int>(width),
      static_cast<int>(height)
  };
  return true;
}

vec3 c_entity::central_position() {
  return origin() + vec3_t(0.0f, 0.0f, (mins().z + maxs().z) * 0.5f);
}