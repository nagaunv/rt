#pragma once

#include <string>
#include <fmt/format.h>
#include <glm/glm.hpp>

#include "float.hpp"

/// \file Import vector and matrix from glm

namespace naga::rt {
  /// 2D vector
  using vec2 = glm::tvec2<float_t>;
  /// 3D vector
  using vec3 = glm::tvec3<float_t>;
  /// 4D vector
  using vec4 = glm::tvec4<float_t>;

  /// 2x2 matrix
  using mat2 = glm::tmat2x2<float_t>;
  /// 3x3 matrix
  using mat3 = glm::tmat3x3<float_t>;
  /// 4x4 matrix
  using mat4 = glm::tmat4x4<float_t>;

  /// dump information to text
  std::string to_string(const vec2& v) {
    return fmt::format("vec2[{0}, {1}]", v.x, v.y);
  }
  /// dump information to text
  std::string to_string(const vec3& v) {
    return fmt::format("vec2[{0}, {1}, {2}]", v.x, v.y, v.z);
  }
  /// dump information to text
  std::string to_string(const vec4& v) {
    return fmt::format("vec2[{0}, {1}, {2}, {3}]", v.x, v.y, v.z, v.w);
  }

  /// dump information to text
  std::string to_string(const mat2& m) {
    return fmt::format(
      "mat2"            //
      "[{0}, {1}]"      //
      "[{2}, {3}]",     //
      m[0][0], m[0][1], //
      m[1][0], m[1][1]);
  }
  /// dump information to text
  std::string to_string(const mat3& m) {
    return fmt::format(
      "mat3"                     //
      "[{0}, {1}, {2}]"          //
      "[{3}, {4}, {5}]"          //
      "[{6}, {7}, {8}]",         //
      m[0][0], m[0][1], m[0][2], //
      m[1][0], m[1][1], m[1][2], //
      m[2][0], m[2][1], m[2][2]);
  }
  /// dump information to text
  std::string to_string(const mat4& m) {
    return fmt::format(
      "mat4"                              //
      "[{0}, {1}, {2}, {3}]"              //
      "[{4}, {5}, {6}, {7}]"              //
      "[{8}, {9}, {10}, {11}]"            //
      "[{12}, {13}, {14}, {15}]",         //
      m[0][0], m[0][1], m[0][2], m[0][3], //
      m[1][0], m[1][1], m[1][2], m[1][3], //
      m[2][0], m[2][1], m[2][2], m[2][3], //
      m[3][0], m[3][1], m[3][2], m[3][3]);
  }
}