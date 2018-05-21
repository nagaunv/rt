#include "primitive.hpp"

namespace naga::rt {
  GeometricPrimitive::GeometricPrimitive(
    const std::shared_ptr<Material>& m,
    const std::shared_ptr<AreaLight>& l,
    const std::shared_ptr<Shape> s)
    : m_material{m}, m_areaLight{l}, m_shape{s} {}

  std::shared_ptr<Material> GeometricPrimitive::getMaterial() {
    return m_material;
  }

  std::shared_ptr<AreaLight> GeometricPrimitive::getAreaLight() {
    return m_areaLight;
  }

  std::shared_ptr<Shape> GeometricPrimitive::getShape() {
    return m_shape;
  }

  GeometricPrimitive::~GeometricPrimitive() {}
} // namespace naga::rt