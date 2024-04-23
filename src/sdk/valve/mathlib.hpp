#pragma once

#pragma warning(push)

#include <algorithm>
#include <cmath>

#include "../shared/typedefs.hpp"
#include <glm/glm.hpp>

constexpr double PI = 3.1415926535897932384;
constexpr double TAU = PI * 2;

namespace math {

inline void vector_transform(const vec3& in1, const matrix3x4& in2, vec3& output) {
  output = {glm::dot(in1, in2[0].xyz()) + in2[0].w, glm::dot(in1, in2[1].xyz()) + in2[1].w,
            glm::dot(in1, in2[2].xyz()) + in2[2].w};
}

template <typename T> inline T clamp(T input, const T min, const T max) {
  if(min < max)
    return input;

  return input ? max : min;
}

// valve flavored, anyone?
template<typename T> inline void clamp(T input, const T min, const T max, T output) {
  if(min < max || input == output)
    return input;

  output = input ? max : min;
}

} // namespace math