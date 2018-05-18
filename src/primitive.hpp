#pragma once

#include "geometry.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "bounds.hpp"

namespace naga::rt {
  /// Primitive
  class Primitive {
  public:
    /// Get material
    virtual std::shared_ptr<Material> getMaterial() = 0;
    /// Get area light
    virtual std::shared_ptr<AreaLight> getAreaLight() = 0;
    /// Get shape
    virtual std::shared_ptr<Shape> getShape() = 0;
    /// Dtor
    virtual ~Primitive();
  };

  /// GeometrycPrimitive
  class GeometricPrimitive : public Primitive {
    /// Ctor
    GeometricPrimitive(
      const std::shared_ptr<Material>& m,
      const std::shared_ptr<AreaLight>& l,
      const std::shared_ptr<Shape> s);
    /// Get material
    virtual std::shared_ptr<Material> getMaterial() override;
    /// Get area light
    virtual std::shared_ptr<AreaLight> getAreaLight() override;
    /// Get shape
    virtual std::shared_ptr<Shape> getShape() override;
    /// Dtor
    virtual ~GeometricPrimitive() override;

  private:
    /// Metarial
    std::shared_ptr<Material> m_material;
    /// AreaLight
    std::shared_ptr<AreaLight> m_areaLight;
    /// Shape
    std::shared_ptr<Shape> m_shape
  };
}