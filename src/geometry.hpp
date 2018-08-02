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

  struct Point2 : Vec2 {
    using Vec2::Vec2;

    const Vec2& vec() const {
      return *this;
    }

    Vec2& vec() {
      return *this;
    }
  };

  struct Point3 : Vec3 {
    using Vec3::Vec3;

    const Vec3& vec() const {
      return *this;
    }

    Vec3& vec() {
      return *this;
    }
  };

  struct Normal3 : Vec3 {
    using Vec3::Vec3;

    const Vec3& vec() const {
      return *this;
    }

    Vec3& vec() {
      return *this;
    }
  };

  template <class T>
  constexpr T pi = static_cast<T>(3.14159265358979323846);

  class Radian;

  class Degree {
  public:
    constexpr Degree() = default;
    constexpr Degree(const Degree&) = default;
    constexpr Degree(Degree&&) = default;
    constexpr Degree& operator=(const Degree&) = default;
    constexpr Degree& operator=(Degree&&) = default;
    constexpr Degree(float_t v) : m_value{v} {}
    constexpr Degree(const Radian& rad);

    constexpr float_t value() const {
      return m_value;
    }

  private:
    float_t m_value = 0.f;
  };

  class Radian {
  public:
    constexpr Radian() = default;
    constexpr Radian(const Radian&) = default;
    constexpr Radian(Radian&) = default;
    constexpr Radian& operator=(const Radian&) = default;
    constexpr Radian& operator=(Radian&&) = default;
    constexpr Radian(float_t v) : m_value{v} {}
    constexpr Radian(const Degree& deg);

    constexpr float_t value() const {
      return m_value;
    }

  private:
    float_t m_value = 0.f;
  };

  constexpr Degree::Degree(const Radian& rad)
    : m_value{180 / pi<float_t> * rad.value()} {}

  constexpr Radian::Radian(const Degree& deg)
    : m_value{pi<float_t> / 180 * deg.value()} {}

} // namespace naga::rt