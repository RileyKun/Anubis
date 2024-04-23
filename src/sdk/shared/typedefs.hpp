#pragma once

typedef char               i8;
typedef short              i16;
typedef int                i32;
typedef long long          i64;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef unsigned long      DWORD;

typedef void*              (*cint_fn)(const char* name, int* return_code);

#include <glm/glm.hpp>

using QAngle = glm::vec3;
using Vector = glm::vec3;
using matrix3x4 = glm::mat3x4;
using matrix4x4 = glm::mat4x4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;