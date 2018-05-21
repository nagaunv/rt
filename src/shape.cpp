#include "shape.hpp"

namespace naga::rt {
  Bounds3 GeometricShape::getBoundingBox() const {
    return Bounds3{(*m_object_to_world) * Vec4(getObjectBound().min(), 1),
                   (*m_object_to_world) * Vec4(getObjectBound().max(), 1)};
  }
}