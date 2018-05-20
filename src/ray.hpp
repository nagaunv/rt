#pragma once

#include <string>
#include <fmt/format.h>

#include "geometry.hpp"

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
    /*constexpr*/ Ray(const Vec3 &o, const Vec3 &d) : m_origin{o}, m_dir{normalize(d)} {}

    /// Get origin
    constexpr const Vec3 &get_origin() const {
      return m_origin;
    }
    /// Get direction
    constexpr const Vec3 &get_dir() const {
      return m_dir;
    }
    /// Set origin
    constexpr void set_origin(const Vec3 &o) {
      m_origin = o;
    }
    /** \brief Set direction
     * Stores normalized direction.
     * \notes: dropping constexpr since glm does not support it.
     */
    /*constexpr*/ void set_dir(const Vec3 &d) {
      m_dir = normalize(d);
    }

    /// Get origin
    constexpr const Vec3 &origin() const {
      return get_origin();
    }
    /// Get direction
    constexpr const Vec3 &dir() const {
      return get_dir();
    }

  private:
    /// Origin
    Vec3 m_origin;
    /// (normalized) Direction
    Vec3 m_dir;
  };

  /** \brief Calculate ray position
   * `origin + t * dir`
   * \notes: dropping constexpr since glm does not support it.
   */
  /*constepxr*/ Vec3 position(const Ray &ray, float_t t) {
    return ray.origin() + t * ray.dir();
  }

  /// dump information to text
  std::string to_string(const Ray &ray) {
    return fmt::format(
      "Ray({0}, {1})", to_string(ray.origin()), to_string(ray.dir()));
  }
}