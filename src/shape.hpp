#pragma once

#include "ray.hpp"
#include "bounds.hpp"
#include "interaction.hpp"

namespace naga::rt {

  /// Shape
  class Shape {
  public:
    /// Calculate Ray-Shape intersection
    virtual bool intersec(
      const Ray& ray, float_t tMin, float_t tMax, Interaction& isec) const = 0;
    /// Get bounding box
    virtual Bounds3 getBoundingBox() const = 0;
    /// Dtor
    virtual ~Shape(){};
  };

  /// GeometricShape
  class GeometricShape : public Shape {
  public:
    /// Bounding box in object space
    virtual Bounds3 getObjectBound() const = 0;
    /// Get bounding box
    virtual Bounds3 getBoundingBox() const override;
  protected:
    /// transform to world coordinate
    std::shared_ptr<const Mat4> m_object_to_world;
    /// transform from world coordinate
    std::shared_ptr<const Mat4> m_world_to_object;
    /// normals reversed?
    bool m_reverse_normal;
  };
}