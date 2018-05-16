#pragma once 

#include <cmath>
#include <fmt/format.h>

#include "geometry.hpp"

namespace naga::rt {

  /// Point3
  class Point3 : vec3 {
  public:
    // inherited ctors
    using vec3::vec3;
    // export base members
    using vec3::x, vec3::y, vec3::z;

    /// Ctor
    constexpr Point3() {}
    /// Crot
    constexpr Point3(const Point3&) = default;
    /// Ctor
    constexpr Point3(Point3&&)      = default;

    /// operator=
    constexpr Point3& operator=(const Point3&) = default;
    /// operator=
    constexpr Point3& operator=(Point3&&)      = default;

    /** \brief Create Point3 from vec3
     * Initialize Point3 as (Origin(0,0,0) + vec)) = vec
     */
    explicit constexpr Point3(const vec3& vec) : vec3(vec) {}
    /** \brief Create Point3 from vec3
     * Initialize Point3 as (Origin(0,0,0) + vec)) = vec
     */
    explicit constexpr Point3(vec3&& vec) : vec3(std::move(vec)) {}

    /** \brief Conversion to vec3
     * vec3 = Point3 - Origin(0,0,0) = Point3
     */
    constexpr const vec3& vec() const {
      return *this;
    }

    /** \brief Conversion to vec3
     * vec3 = Point3 - Origin(0,0,0) = Point3
     */
    constexpr vec3& vec() {
      return *this;
    }

    /// operator+=
    Point3& operator+=(const vec3& p) {
      vec() += p;
      return *this;
    }

    /// operator-=
    Point3& operator-=(const vec3& p) {
      vec() -= p;
      return *this;
    }

    /// operator==
    friend bool operator==(const Point3& lhs, const Point3& rhs) {
      return lhs.vec() == rhs.vec();
    }
  };

  /// Point2
  class Point2 : vec2 {
  public:
    // inherited ctors
    using vec2::vec2;
    // export base members
    using vec2::x, vec2::y;

    /// Ctor
    constexpr Point2() {}
    /// Crot
    constexpr Point2(const Point2&) = default;
    /// Ctor
    constexpr Point2(Point2&&) = default;

    /// operator=
    constexpr Point2& operator=(const Point2&) = default;
    /// operator=
    constexpr Point2& operator=(Point2&&) = default;

    /** \brief Create Point2 from vec2
     * Initialize Point2 as (Origin(0,0) + vec)) = vec
     */
    explicit constexpr Point2(const vec2& vec) : vec2(vec) {}
    /** \brief Create Point2 from vec2
     * Initialize Point2 as (Origin(0,0) + vec)) = vec
     */
    explicit constexpr Point2(vec2&& vec) : vec2(std::move(vec)) {}

    /** \brief Conversion to vec2
     * vec2 = Point2 - Origin(0,0) = Point2
     */
    constexpr const vec2& vec() const {
      return *this;
    }

    /** \brief Conversion to vec2
     * vec2 = Point2 - Origin(0,0) = Point2
     */
    constexpr vec2& vec() {
      return *this;
    }

    /// operator+=
    Point2& operator+=(const vec2& p) {
      vec() += p;
      return *this;
    }

    /// operator-=
    Point2& operator-=(const vec2& p) {
      vec() -= p;
      return *this;
    }

    /// operator==
    friend bool operator==(const Point2& lhs, const Point2& rhs) {
      return lhs.vec() == rhs.vec();
    }
  };

  /// operator+
  Point3 operator+(const Point3& lhs, const vec3& rhs) {
    Point3 tmp(lhs);
    return tmp += rhs;
  }
  /// operator-
  Point3 operator-(const Point3& lhs, const vec3& rhs) {
    Point3 tmp(lhs);
    return tmp -= rhs;
  }

  /// operator+
  Point2 operator+(const Point2& lhs, const vec2& rhs) {
    Point2 tmp(lhs);
    return tmp += rhs;
  }
  /// operator-
  Point2 operator-(const Point2& lhs, const vec2& rhs) {
    Point2 tmp(lhs);
    return tmp -= rhs;
  }

  /// Calculate distance
  float_t distance(const Point3& lhs, const Point3& rhs){
    return distance(lhs.vec(), rhs.vec());
  }

  /// Calculate distance
  float_t distance(const Point2& lhs, const Point2& rhs){
    return distance(lhs.vec(), rhs.vec());
  }

  /// dump information to string
  std::string to_string(const Point3& p){
    return fmt::format("Point3({0}, {1}, {2})", p.x, p.y, p.z);
  }

  /// dump information to string
  std::string to_string(const Point2& p){
    return fmt::format("Point3({0}, {1})", p.x, p.y);
  }

} // namespace naga::rt