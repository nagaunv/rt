#include "RGB.hpp"
#include <algorithm>

namespace naga::rt {

  Vec3 XYZToRGB(const Vec3& xyz) {
    Vec3 ret{};

    // convert color space
    ret[0] = +3.2406 * xyz[0] - 1.5372 * xyz[1] - 0.4986 * xyz[2];
    ret[1] = -0.9689 * xyz[0] + 1.8758 * xyz[1] + 0.0415 * xyz[2];
    ret[2] = +0.0557 * xyz[0] - 0.2040 * xyz[1] + 1.0570 * xyz[2];

    // gamma correction
    auto gamma = [](auto c) {
      if (c <= 0.0031308)
        return 12.92 * c;
      else
        return fms(1.055, std::pow(c, 1 / 2.4), 0.055);
    };

    ret[0] = gamma(ret[0]);
    ret[1] = gamma(ret[1]);
    ret[2] = gamma(ret[2]);

    // clamp
    ret[0] = std::clamp(ret[0], 0.f, 1.f);
    ret[1] = std::clamp(ret[1], 0.f, 1.f);
    ret[2] = std::clamp(ret[2], 0.f, 1.f);

    return ret;
  }

  RGBColor::RGBColor(const Vec3& vec) : value{vec[0], vec[1], vec[2]} {};

  const float_t& RGBColor::operator[](size_t i) const {
    return value[i];
  }

  float_t& RGBColor::operator[](size_t i) {
    return value[i];
  }

  Vec3 RGBColor::to_vec() const {
    return {r, g, b};
  }

  XYZColor RGBColor::to_xyz() const {
    return {RGBToXYZ(to_vec())};
  }
}