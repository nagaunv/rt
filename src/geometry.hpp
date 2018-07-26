#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "float.hpp"

/// \file Import vector and matrix from glm

namespace naga::rt {
  /// 2D vector
  using Vec2 = glm::tvec2<float_t>;
  /// 3D vector
  using Vec3 = glm::tvec3<float_t>;
  /// 4D vector
  using Vec4 = glm::tvec4<float_t>;

  /// 2x2 matrix
  using Mat2 = glm::tmat2x2<float_t>;
  /// 3x3 matrix
  using Mat3 = glm::tmat3x3<float_t>;
  /// 4x4 matrix
  using Mat4 = glm::tmat4x4<float_t>;

  /// quat
  using Quat = glm::tquat<float_t>;

  /// dump information to text
  std::string to_string(const Vec2& v);
  /// dump information to text
  std::string to_string(const Vec3& v);
  /// dump information to text
  std::string to_string(const Vec4& v);
  /// dump information to text
  std::string to_string(const Quat& q);

  /// dump information to text
  std::string to_string(const Mat2& m);
  /// dump information to text
  std::string to_string(const Mat3& m);
  /// dump information to text
  std::string to_string(const Mat4& m);
}