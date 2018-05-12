#pragma once

#include <string>
#include <fmt/format.h>
#include <glm/glm.hpp>

namespace naga::rt {
  // vec
  using vec2 = glm::dvec2;
  using vec3 = glm::dvec3;
  using vec4 = glm::dvec4;

  // mat
  using mat2 = glm::dmat2;
  using mat3 = glm::dmat3;
  using mat4 = glm::dmat4;

  std::string to_string(const vec2& v) {
    return fmt::format("vec2[{0}, {1}]", v.x, v.y);
  }
  std::string to_string(const vec3& v) {
    return fmt::format("vec2[{0}, {1}, {2}]", v.x, v.y, v.z);
  }
  std::string to_string(const vec4& v) {
    return fmt::format("vec2[{0}, {1}, {2}, {3}]", v.x, v.y, v.z, v.w);
  }

  std::string to_string(const mat2& m) {
    return fmt::format(
      "mat2"            //
      "[{0}, {1}]"      //
      "[{2}, {3}]",     //
      m[0][0], m[0][1], //
      m[1][0], m[1][1]);
  }
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