#pragma once

#include "float.hpp"
#include "geometry.hpp"

namespace naga::rt {

  /// Transform
  class Transform {
  public:
    Transform(const Transform&) = default;
    Transform(Transform&&) = default;
    Transform& operator=(const Transform&) = default;
    Transform& operator=(Transform&&) = default;

    /// Create identity transform
    Transform() : m_matrix{1.0}, m_inverse{1.0} {}

    /// Construct from 2 matrix
    Transform(const Mat4& mat, const Mat4& inv) //
      : m_matrix{mat}, m_inverse{inv} {}

    /// Construct from matrix
    Transform(const Mat4& mat) //
      : m_matrix{mat}, m_inverse{glm::inverse(mat)} {};

    /// get matrix
    const Mat4& getMatrix() const {
      return m_matrix;
    }

    /// get inverse
    const Mat4& getInverseMatrix() const {
      return m_inverse;
    }

    /// check identity
    bool isIdentity() const {
      auto id = Mat4(1);
      return id == m_matrix && id == m_inverse;
    }

    /// create inverse transform
    Transform inverse() const;

    /// translate
    static Transform translate(const Vec3& v);
    /// scale
    static Transform scale(const Vec3& v);
    /// rotate 
    static Transform rotate(Radian angle, const Vec3& v);
    /// rotate to arbitrary axis
    static Transform rotate(const Vec3& axis, Radian angle);

    Vec3 operator()(const Vec3& vec) {
      auto ret = m_matrix * Vec4(vec, 1);
      return ret / ret.w;
    }

  protected:
    Mat4 m_matrix;
    Mat4 m_inverse;
  };

  /// operator==
  bool operator==(const Transform& lhs, const Transform& rhs) {
    return lhs.getMatrix() == rhs.getMatrix() &&
           lhs.getInverseMatrix() == rhs.getInverseMatrix();
  }

  /// operator==
  bool operator!=(const Transform& lhs, const Transform& rhs) {
    return !(lhs == rhs);
  }

  /// create inverse transform
  Transform Transform::inverse() const {
    return {m_inverse, m_matrix};
  }

  Transform Transform::translate(const Vec3& v) {
    return {glm::translate(Mat4(1), v)};
  }

  Transform Transform::scale(const Vec3& v) {
    return {glm::scale(Mat4(1), v)};
  }

  Transform Transform::rotate(Radian angle, const Vec3& v) {
    return {glm::rotate(Mat4(1), angle.value(), v)};
  }

  /// rotate to arbitrary axis
  Transform Transform::rotate(const Vec3& axis, Radian angle) {
    auto cos = std::cos(angle.value());
    auto sin = std::sin(angle.value());
    auto n1 = axis.x;
    auto n2 = axis.y;
    auto n3 = axis.z;

    Vec4 c1 = {cos + std::pow(n1, 2) * (1 - cos), //
               n2 * n1 * (1 - cos) + n3 * sin,    //
               n3 * n1 * (1 - cos) - n2 * sin,    //
               0};                                //

    Vec4 c2 = {n1 * n2 * (1 - cos) - n3 * sin,    //
               cos + std::pow(n2, 2) * (1 - cos), //
               n3 * n2 * (1 - cos) + n1 * sin,    //
               0};                                //

    Vec4 c3 = {n1 * n3 * (1 - cos) + n2 * sin,    //
               n2 * n3 * (1 - cos) - n1 * sin,    //
               cos - std::pow(n3, 2) * (1 - cos), //
               0};                                //

    Vec4 c4 = {0, 0, 0, 1};
    return Transform(Mat4(c1, c2, c3, c4));
  }
}