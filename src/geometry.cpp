#include "geometry.hpp"
#include <fmt/format.h>

namespace naga::rt {
  /// dump information to text
  std::string to_string(const Vec2& v) {
    return fmt::format("Vec2[{0}, {1}]", v.x, v.y);
  }
  /// dump information to text
  std::string to_string(const Vec3& v) {
    return fmt::format("Vec2[{0}, {1}, {2}]", v.x, v.y, v.z);
  }
  /// dump information to text
  std::string to_string(const Vec4& v) {
    return fmt::format("Vec2[{0}, {1}, {2}, {3}]", v.x, v.y, v.z, v.w);
  }
  /// dump information to text
  std::string to_string(const Quat& q) {
    return fmt::format("Quat[{0}, {1}, {2}, {3}]", q.x, q.y, q.z, q.w);
  }

  /// dump information to text
  std::string to_string(const Mat2& m) {
    return fmt::format(
      "Mat2"            //
      "[{0}, {1}]"      //
      "[{2}, {3}]",     //
      m[0][0], m[0][1], //
      m[1][0], m[1][1]);
  }
  /// dump information to text
  std::string to_string(const Mat3& m) {
    return fmt::format(
      "Mat3"                     //
      "[{0}, {1}, {2}]"          //
      "[{3}, {4}, {5}]"          //
      "[{6}, {7}, {8}]",         //
      m[0][0], m[0][1], m[0][2], //
      m[1][0], m[1][1], m[1][2], //
      m[2][0], m[2][1], m[2][2]);
  }
  /// dump information to text
  std::string to_string(const Mat4& m) {
    return fmt::format(
      "Mat4"                              //
      "[{0}, {1}, {2}, {3}]"              //
      "[{4}, {5}, {6}, {7}]"              //
      "[{8}, {9}, {10}, {11}]"            //
      "[{12}, {13}, {14}, {15}]",         //
      m[0][0], m[0][1], m[0][2], m[0][3], //
      m[1][0], m[1][1], m[1][2], m[1][3], //
      m[2][0], m[2][1], m[2][2], m[2][3], //
      m[3][0], m[3][1], m[3][2], m[3][3]);
  }
}