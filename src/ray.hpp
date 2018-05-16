#pragma once

#include <string>
#include <fmt/format.h>

#include "point.hpp"

/// \file Ray definition

namespace naga::rt {

  /// Ray
  class Ray {
  public:
    /// Ctor
    constexpr Ray() : m_origin{}, m_dir{} {}
    /// Ctor
    constexpr Ray(const Ray &) = default;
    /// Ctor
    constexpr Ray(Ray &&)      = default;
    /// Dtor
    ~Ray()                     = default;

    /// operator=
    constexpr Ray &operator=(const Ray &) = default;
    /// operator=
    constexpr Ray &operator=(Ray &&)      = default;

    /** \brief Ctor
     * Stores origin and normalized direction.  
     * \notes: dropping constexpr since glm does not support it.
     */
    /*constexpr*/ Ray(const Point3 &o, const vec3 &d) : m_origin{o}, m_dir{normalize(d)} {}

    /// Get origin
    constexpr const Point3 &get_origin() const {
      return m_origin;
    }
    /// Get direction
    constexpr const vec3 &get_dir() const {
      return m_dir;
    }
    /// Set origin
    constexpr void set_origin(const Point3 &o) {
      m_origin = o;
    }
    /** \brief Set direction
     * Stores normalized direction.
     * \notes: dropping constexpr since glm does not support it.
     */
    /*constexpr*/ void set_dir(const vec3 &d) {
      m_dir = normalize(d);
    }

    /// Get origin
    constexpr const Point3 &origin() const {
      return get_origin();
    }
    /// Get direction
    constexpr const vec3 &dir() const {
      return get_dir();
    }

  private:
    /// Origin
    Point3 m_origin;
    /// (normalized) Direction
    vec3 m_dir;
  };

  /** \brief Calculate ray position
   * `origin + t * dir`
   * \notes: dropping constexpr since glm does not support it.
   */
  /*constepxr*/ Point3 position(const Ray &ray, float_t t) {
    return ray.origin() + t * ray.dir();
  }

  /// dump information to text
  std::string to_string(const Ray &ray) {
    return fmt::format(
      "Ray({0}, {1})", to_string(ray.origin()), to_string(ray.dir()));
  }
}