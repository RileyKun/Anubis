#pragma once

// full credits to JAGNEmk for the math library
// NOTE: Riley; ignore the formatting, i'm still trying to figure out clang-format

#pragma warning(push)

#include <algorithm>
#include <cmath>

constexpr double              PI = 3.1415926535897932384;
constexpr double              TAU = PI * 2;

__forceinline constexpr float deg2rad(float value) {
  return value * static_cast<float>(static_cast<double>(PI) / 180);
}

__forceinline constexpr float rad2deg(float value) {
  return value * static_cast<float>(180.f / static_cast<double>(PI));
}

struct rect_t {
  int x, y, w, h;
};

using matrix3x4 = float[3][4];

namespace math {

inline void sine_cosine(const float& radians, float& sine, float& cosine) {
  sine = sin(radians);
  cosine = cos(radians);
}

inline float remap_value(float value, float a, float b, float c, float d) {
  if(a == b) {
    return value >= b ? d : c;
  }
  return c + (d - c) * (value = a) / (b - a);
}

inline float remap_value_clamped(float value, float a, float b, float c, float d) {
  if(a == b) {
    return value >= b ? d : c;
  }
  float c_value = (value - a) / (b - a);
  c_value = std::clamp(c_value, 0.0f, 1.0f);

  return c + (d - c) * c_value;
}

// blarg
__forceinline float remap(float value, float a, float b, float c, float d) {
  return remap_value_clamped(value, a, b, c, d);
}
} // namespace math

class vec4_t {
public:
  float x, y, z, h;
};

class vec2_t {
public:
  float x, y;

  vec2_t() { x = y = 0.0f; }

  vec2_t(float X, float Y) {
    x = X;
    y = Y;
  }

  vec2_t(float* v) {
    x = v[0];
    y = v[1];
  }

  vec2_t(const float* v) {
    x = v[0];
    y = v[1];
  }

  vec2_t(const vec2_t& v) {
    x = v.x;
    y = v.y;
  }

  vec2_t& operator=(const vec2_t& v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  float&  operator[](int i) { return ((float*)this)[i]; }

  float   operator[](int i) const { return ((float*)this)[i]; }

  vec2_t& operator+=(const vec2_t& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  vec2_t& operator-=(const vec2_t& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  vec2_t& operator*=(const vec2_t& v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }

  vec2_t& operator/=(const vec2_t& v) {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  vec2_t& operator+=(float v) {
    x += v;
    y += v;
    return *this;
  }

  vec2_t& operator-=(float v) {
    x -= v;
    y -= v;
    return *this;
  }

  vec2_t& operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
  }

  vec2_t& operator/=(float v) {
    x /= v;
    y /= v;
    return *this;
  }

  vec2_t operator+(const vec2_t& v) const { return {x + v.x, y + v.y}; }

  vec2_t operator-(const vec2_t& v) const { return {x - v.x, y - v.y}; }

  vec2_t operator*(const vec2_t& v) const { return {x * v.x, y * v.y}; }

  vec2_t operator/(const vec2_t& v) const { return {x / v.x, y / v.y}; }

  vec2_t operator+(float v) const { return {x + v, y + v}; }

  vec2_t operator-(float v) const { return {x - v, y - v}; }

  vec2_t operator*(float v) const { return {x * v, y * v}; }

  vec2_t operator/(float v) const { return {x / v, y / v}; }

  void   set(float X = 0.0f, float Y = 0.0f) {
    x = X;
    y = Y;
  }

  float length(void) const { return sqrtf(x * x + y * y); }

  float length_sqr(void) const { return (x * x + y * y); }

  float dist_to(const vec2_t& v) const { return (*this - v).length(); }

  float dist_to_sqr(const vec2_t& v) const { return (*this - v).length_sqr(); }

  float dot(const vec2_t& v) const { return (x * v.x + y * v.y); }

  bool  is_zero(void) const {
    return (x > -FLT_EPSILON && x < FLT_EPSILON && y > -FLT_EPSILON && y < FLT_EPSILON);
  }

  operator bool() const noexcept { return !is_zero(); }
};

class vec3_t {
public:
  float x, y, z;

  vec3_t() { x = y = z = 0.0f; }

  vec3_t(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
  }

  vec3_t(float* v) {
    x = v[0];
    y = v[1];
    z = v[2];
  }

  vec3_t(const float* v) {
    x = v[0];
    y = v[1];
    z = v[2];
  }

  vec3_t(const vec3_t& v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  vec3_t(const vec2_t& v) {
    x = v.x;
    y = v.y;
    z = 0.0f;
  }

  __forceinline vec3_t& operator=(const vec3_t& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  __forceinline vec3_t& operator=(const vec2_t& v) {
    x = v.x;
    y = v.y;
    z = 0.0f;
    return *this;
  }

  float&              operator[](int i) { return reinterpret_cast<float*>(this)[i]; }

  __forceinline float operator[](int i) const { return ((float*)this)[i]; }

  vec3_t&             operator+=(const vec3_t& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  vec3_t& operator-=(const vec3_t& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  vec3_t& operator*=(const vec3_t& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  vec3_t& operator/=(const vec3_t& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  vec3_t& operator+=(float v) {
    x += v;
    y += v;
    z += v;
    return *this;
  }

  vec3_t& operator-=(float v) {
    x -= v;
    y -= v;
    z -= v;
    return *this;
  }

  vec3_t& operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  vec3_t& operator/=(float v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }

  __forceinline vec3_t operator+(const vec3_t& v) const {
    return {x + v.x, y + v.y, z + v.z};
  }

  __forceinline vec3_t operator-(const vec3_t& v) const {
    return {x - v.x, y - v.y, z - v.z};
  }

  __forceinline vec3_t operator*(const vec3_t& v) const {
    return {x * v.x, y * v.y, z * v.z};
  }

  __forceinline vec3_t operator/(const vec3_t& v) const {
    return {x / v.x, y / v.y, z / v.z};
  }

  __forceinline vec3_t operator+(float v) const { return {x + v, y + v, z + v}; }

  __forceinline vec3_t operator-(float v) const { return {x - v, y - v, z - v}; }

  __forceinline vec3_t operator*(float v) const { return {x * v, y * v, z * v}; }

  __forceinline vec3_t operator/(float v) const { return {x / v, y / v, z / v}; }

  __forceinline float  length() const { return sqrtf(x * x + y * y + z * z); }

  __forceinline float  length_sqr() const { return (x * x + y * y + z * z); }

  __forceinline float  length_2d() const { return sqrtf(x * x + y * y); }

  __forceinline float  length_2d_sqr() const { return (x * x + y * y); }

  __forceinline float  dist_to(const vec3_t& v) const { return (*this - v).length(); }

  __forceinline float  dist_to_sqr(const vec3_t& v) const { return (*this - v).length_sqr(); }

  __forceinline float  dot(const vec3_t& v) const { return (x * v.x + y * v.y + z * v.z); }

  inline vec3_t        to_vec() const {
    auto  out = vec3_t();
    float sp, sy, cp, cy;

    math::sine_cosine(deg2rad(x), sp, cp);
    math::sine_cosine(deg2rad(y), sy, cy);

    out.x = cp * cy;
    out.y = cp * sy;
    out.z = -sp;

    return out;
  }

  inline void angle_vectors(vec3_t* forward) const {
    float sp, sy, cp, cy;

    math::sine_cosine(deg2rad(x), sp, cp);
    math::sine_cosine(deg2rad(y), sy, cy);

    if(forward) {
      forward->x = cp * cy;
      forward->y = cp * sy;
      forward->z = -sp;
    }
  }

  inline vec3_t vel_to_ang() const {
    auto magnitude = [&](const vec3_t& v) -> float {
      return sqrtf(v.dot(v));
    };

    float yaw, pitch;

    if(y == 0.f && x == 0.f) {
      yaw = 0.0f;

      if(z > 0.f)
        pitch = 270.f;

      else
        pitch = 90.f;
    } else {
      yaw = rad2deg(::atan2f(y, x));
      pitch = rad2deg(::atan2f(-z, magnitude(*this)));

      if(yaw < 0.f)
        yaw += 360.f;

      if(pitch < 0.f)
        pitch += 360.f;
    }

    return {pitch, yaw, 0.f};
  }

  inline void angle_vectors(vec3_t* forward, vec3_t* right, vec3_t* up) const {
    float sr, sp, sy, cr, cp, cy;
    math::sine_cosine(deg2rad(x), sp, cp);
    math::sine_cosine(deg2rad(y), sy, cy);
    math::sine_cosine(deg2rad(z), sr, cr);

    if(forward) {
      forward->x = cp * cy;
      forward->y = cp * sy;
      forward->z = -sp;
    }

    if(right) {
      right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
      right->y = (-1 * sr * sp * sy + -1 * cr * cy);
      right->z = -1 * sr * cp;
    }

    if(up) {
      up->x = (cr * sp * cy + -sr * -sy);
      up->y = (cr * sp * sy + -sr * cy);
      up->z = cr * cp;
    }
  }

  __forceinline vec3_t look(vec3_t to) const {
    to -= *this;
    vec3_t angles;
    if(to.y == 0.0f && to.x == 0.0f) {
      angles.x = (to.z > 0.0f) ? 270.0f : 90.0f;
      angles.y = 0.0f;
    } else {
      angles.x = rad2deg(::atan2f(-to.z, to.length_2d()));
      angles.y = rad2deg(::atan2f(to.y, to.x));
    }

    angles.z = 0.0f;
    return angles;
  }

  __forceinline float fov_to(const vec3_t& to) {
    vec3_t v_src = vec3_t();
    angle_vectors(&v_src);

    vec3_t v_dst = vec3_t();
    to.angle_vectors(&v_dst);

    float result = rad2deg(::acosf(v_dst.dot(v_src) / v_dst.length_sqr()));

    if(!::isfinite(result) || ::isinf(result) || ::isnan(result))
      result = 0.0f;

    return result;
  }

  vec3_t cross(const vec3_t& v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
  }

  bool is_zero() const {
    return (x > -FLT_EPSILON && x < FLT_EPSILON && y > -FLT_EPSILON && y < FLT_EPSILON &&
            z > -FLT_EPSILON && z < FLT_EPSILON);
  }

  operator bool() const { return !is_zero(); }

  inline void normalize_vector() {
    vec3_t& v = *this;

    float   iradius = 1.f / (length() + FLT_EPSILON); // FLT_EPSILON

    v.x *= iradius;
    v.y *= iradius;
    v.z *= iradius;
  }

  vec3_t abs() const { return vec3_t{std::abs(x), std::abs(y), std::abs(z)}; }

  vec3_t clamp() {
    for(size_t axis{}; axis < 2; axis++) {
      auto& cur_axis = operator[](axis);
      if(!std::isfinite(cur_axis)) {
        cur_axis = 0.f;
      }
    }

    x = std::clamp(x, -89.f, 89.f);
    y = std::clamp(std::remainder(y, 360.f), -180.f, 180.f);
    z = 0.f;
    return *this;
  }

  vec3_t transform(const matrix3x4& matrix) const {
    auto out = vec3_t();

    for(auto i = 0; i < 3; i++)
      out[i] = dot((vec3_t&)matrix[i]) + matrix[i][3];

    return out;
  }
};

namespace mathex {
  inline void vector_transform(const vec3_t& input, const matrix3x4& matrix, vec3_t& output){
    for(auto i = 0; i < 3; ++i) {
      output[i] = input.dot((vec3_t&)matrix[i]) + matrix[i][3];
    }
  }

}

using QAngle = vec3_t;
using vec3 = vec3_t;
using vec2 = vec2_t;
using Vector = vec3_t;

#pragma warning(pop)