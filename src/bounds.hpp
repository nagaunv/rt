#pragma once

#include "geometry.hpp"

#include <cstddef>
#include <cassert>
#include <utility>

/// \file Bounds3

namespace naga::rt {
  /// Axis-aligned bouding box
  class Bounds3 {
  public:
    /// Ctor
    constexpr Bounds3() : m_min{}, m_max{} {}
    /// Ctor
    /*constexpr*/ Bounds3(const Vec3& p1, const Vec3& p2)
      : m_min{glm::min(p1, p2)}, m_max{glm::max(p1, p2)} {}

    /// Ctor
    /// Initialize pMin and pMax by single point.
    constexpr Bounds3(const Vec3& p) :m_min{p}, m_max{p} {}

    /// Get pMin
    constexpr const Vec3& getMin() const {
      return m_min;
    }
    /// Get pMax
    constexpr const Vec3& getMax() const {
      return m_max;
    }
    /// Set pMin
    constexpr void setMin(const Vec3& p) {
      m_min = p;
    }
    /// Set pMin
    constexpr void setMax(const Vec3& p) {
      m_max = p;
    }

    /// Get pMin
    constexpr const Vec3& min() const {
      return getMin();
    }
    /// Get pMax
    constexpr const Vec3& max() const {
      return getMax();
    }

    /** \brief Get point of corner.
     * Corner flag bits:  
     *           p_max  
     *       +----+  ->   110  111  
     *      /|   /|  
     *     +----+ |  -> 100  101  
     *     | +- | +  ->   010  011  
     *     |/   | /  
     *     +----+    -> 000  001  
     *  p_min  
     *  
     */
    constexpr Vec3 corner(unsigned char id) const {
      assert(id < 8);
      return Vec3{id & 1 ? max().x : min().x, 
                  id & 2 ? max().y : min().y,
                  id & 4 ? max().z : min().z};
    }

    /// Get center of the bounding box
    /*constexpr*/ Vec3 center() const {
      return {(m_min + m_max) / 2.f};
    }
    /// Get new bounding box which includes given 2 bounding boxes
    static /*constexpr*/ Bounds3 merge(const Bounds3& b1, const Bounds3& b2) {
      return {glm::min(b1.min(), b2.min()), glm::max(b1.max(), b2.max())};
    }
    // Get new bounding box which includes given bouding box and point
    static /*constexpr*/ Bounds3 merge(const Bounds3& box, const Vec3& point) {
      return {glm::min(box.m_min, point), glm::max(box.m_max, point)};
    }

    /// Compute intersection
    bool intersec(const Ray& ray, float_t tMin, float_t tMax) {
      // calculate Ray/Plane intersections.
      Vec3 d = Vec3(1) / ray.dir();
      Vec3 Near = (m_min - ray.origin()) * d;
      Vec3 Far = (m_max - ray.origin()) * d;
      // loop
      float_t t0 = tMin;
      float_t t1 = tMax;
      for (auto i = 0; i < 3; ++i) {
        if (Near[i] > Far[i]) std::swap(Near[i], Far[i]);
        t0 = Near[i] > t0 ? Near[i] : t0;
        t1 = Far[i] < t1 ? Far[i] : t1;
        if (t0 > t1) return false;
      }
      return true;
    }

  private:
    Vec3 m_min;
    Vec3 m_max;
  };
}