#pragma once

#include <fmt/format.h>

#include "geometry.hpp"
#include "point.hpp"

namespace naga::rt {
  /// Normal
  class Normal3 : vec3 {
  public:
    // inherited ctors
    using vec3::vec3;
    // export base members
    using vec3::x, vec3::y, vec3::z;

    /// Ctor
    constexpr Normal3() {}
    /// Ctor
    constexpr Normal3(const Normal3&) = default;
    /// Ctor
    constexpr Normal3(Normal3&&)      = default;

    /// operator==
    constexpr Normal3& operator=(const Normal3&) = default;
    /// operator==
    constexpr Normal3& operator=(Normal3&)       = default;

    /// Create Normal3 from vec3
    explicit constexpr Normal3(const vec3& vec) : vec3(vec) {}
    /// Create Normal3 from vec3
    explicit constexpr Normal3(vec3&& vec) : vec3(std::move(vec)) {}

    /// Get vec3
    constexpr const vec3& vec() const {
      return *this;
    }

    /// Get vec3
    constexpr vec3& vec() {
      return *this;
    }
  };

  /// normalize
  Normal3 normalize(const Normal3& normal) {
    return Normal3(normalize(normal.vec()));
  }

  /// faceforward (GLSL, not pbrt)
  Normal3 faceforward(
    const Normal3& normal, const vec3& incident, const Normal3& normal_ref) {
    return Normal3(faceforward(normal.vec(), incident, normal_ref.vec()));
  }

  /// reflect
  vec3 reflect(const vec3& incident, const Normal3& normal) {
    return reflect(incident, normal.vec());
  }

  /// refract
  vec3 refract(const vec3& incident, const Normal3& normal, float_t eta) {
    return refract(incident, normal.vec(), eta);
  }

  /// dump information to string
  std::string to_string(const Normal3& n) {
    return fmt::format("Normal3({0}, {1}, {2})", n.x, n.y, n.z);
  }
}