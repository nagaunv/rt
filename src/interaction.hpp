#pragma once

#include <variant>

#include "geometry.hpp"
#include "material.hpp"
#include "light.hpp"
//#include "shape.hpp"
#include "bsdf.hpp"
#include "bssrdf.hpp"

namespace naga::rt {

  // forward decl Shape
  class Shape;

  class SurfaceInteraction {
    SurfaceInteraction() = default;
    SurfaceInteraction(const SurfaceInteraction&) = default;
    SurfaceInteraction(SurfaceInteraction&&) = default;
    SurfaceInteraction& operator=(const SurfaceInteraction&) = default;
    SurfaceInteraction& operator=(SurfaceInteraction&&) = default;
    ~SurfaceInteraction() = default;
    /// Ctor
    SurfaceInteraction(
      float_t t,
      const Vec3& p,
      const Vec3& p_err,
      const Vec3& in,
      const Vec2& uv,
      const Vec3& dpdu,
      const Vec3& dpdv,
      const Vec3& dndu,
      const Vec3& dndv,
      const std::shared_ptr<Shape> s)
      : m_t{t}
      , m_pos{p}
      , m_pos_error{p_err}
      , m_incident{in}
      , m_uv{uv}
      , m_geometry{{cross(dpdu, dpdv), dpdu, dpdv, dndu, dndv},
                   {m_geometry.surface}}
      , m_bsdf{nullptr}
      , m_bssrdf{nullptr}
      , m_shape{s} {}

    /// t
    float_t t() const {
      return m_t;
    }
    /// position
    const Vec3& pos() const {
      return m_pos;
    }
    /// position error
    const Vec3& pos_error() const {
      return m_pos_error;
    }
    /// incident vector
    const Vec3& incident() const {
      return m_incident;
    }
    /// uv coordinate
    const Vec2& uv() const {
      return m_uv;
    }
    /// shading geometry
    const auto& shadingGeometry() const {
      return m_geometry.shading;
    }
    /// surface geometry
    const auto& surfaceGeometry() const {
      return m_geometry.surface;
    }
    /// BSDF
    const std::shared_ptr<BSDF>& bsdf() {
      return m_bsdf;
    }
    /// BSSRDF
    const std::shared_ptr<BSSRDF>& bssrdf() {
      return m_bssrdf;
    }

    /// Set BSDF
    void setBSDF(const std::shared_ptr<BSDF>& p) {
      m_bsdf = p;
    }
    /// Set BSDF
    void setBSDF(std::shared_ptr<BSDF>&& p) {
      m_bsdf = std::move(p);
    }
    /// Set BSSRDF
    void setBSSRDF(const std::shared_ptr<BSSRDF>& p) {
      m_bssrdf = p;
    }
    /// Set BSSRDF
    void setBSSRDF(std::shared_ptr<BSSRDF>&& p) {
      m_bssrdf = std::move(p);
    }
    /// Set shading geometry
    void setShadingGeometry(
      const Vec3& normal,
      const Vec3& dpdu,
      const Vec3& dpdv,
      const Vec3& dndu,
      const Vec3& dndv) {
      m_geometry.shading = {
        normal, dpdu, dpdv, dndu, dndv,
      };
    }

  private:
    /// Ray hit parameter
    float_t m_t;
    /// hit position
    Vec3 m_pos;
    /// hit position error
    Vec3 m_pos_error;
    /// incident direction
    Vec3 m_incident;
    /// UV(texture) coordinate
    Vec2 m_uv;
    /// geometry information
    struct {
      struct {
        /// normal at hit position
        Vec3 normal;
        /// ∂p/∂u, ∂p/∂v
        /// n ≡ cross(dpdu, dpdv)
        Vec3 dpdu, dpdv;
        /// ∂n/∂u, ∂n/∂v
        Vec3 dndu, dndv;
      } surface, shading;
    } m_geometry;
    /// BSDF
    std::shared_ptr<BSDF> m_bsdf;
    /// BSSRDF
    std::shared_ptr<BSSRDF> m_bssrdf;
    /// Shape
    std::shared_ptr<Shape> m_shape;
  };

  struct MediumInteraction {
    // TODO
  };

  /// Interaction
  using Interaction =
    std::variant<std::monostate, SurfaceInteraction, MediumInteraction>;
}