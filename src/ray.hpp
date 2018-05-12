#pragma once

#include <string>
#include <fmt/format.h>
#include "geometry.hpp"

namespace naga::rt {

  class Ray {
  public:
    constexpr Ray() : m_origin{}, m_dir{} {}
    constexpr Ray(const Ray &) = default;
    constexpr Ray(Ray &&)      = default;
    ~Ray()                     = default;

    constexpr Ray &operator=(const Ray &) = default;
    constexpr Ray &operator=(Ray &&)      = default;

    /// \notes: dropping constexpr since glm does not support it.
    /*constexpr*/ Ray(const vec3 &o, const vec3 &d) : m_origin{o}, m_dir{normalize(d)} {}

    constexpr const vec3 &origin() const {
      return m_origin;
    }
    constexpr const vec3 &dir() const {
      return m_dir;
    }

    constexpr const vec3 &get_origin() const {
      return origin();
    }
    constexpr const vec3 &get_dir() const {
      return dir();
    }

    constexpr void set_origin(const vec3 &o) {
      m_origin = o;
    }

    /// \notes: dropping constexpr since glm does not support it.
    /*constexpr*/ void set_dir(const vec3 &d) {
      m_dir = normalize(d);
    }

  private:
    vec3 m_origin;
    vec3 m_dir;
  };

  /// \notes: dropping constexpr since glm does not support it.
  /*constepxr*/ vec3 position(const Ray &ray, double t) {
    return ray.origin() + t * ray.dir();
  }

  std::string to_string(const Ray &ray) {
    return fmt::format(
      "Ray({0}, {1})", to_string(ray.origin()), to_string(ray.dir()));
  }
}