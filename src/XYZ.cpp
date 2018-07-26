#include "XYZ.hpp"
#include "RGB.hpp"

#include <algorithm>


namespace naga::rt {

  /// Convert sRGB color to XYZ color space
  Vec3 RGBToXYZ(const Vec3& rgb) {
    Vec3 ret{};

    // gamma correction
    auto gamma = [](auto c) {
      if (c <= 0.04045)
        return c / 12.92;
      else
        return std::pow((c + 0.055) / (1.055), 2.4);
    };

    ret[0] = gamma(rgb[0]);
    ret[1] = gamma(rgb[1]);
    ret[2] = gamma(rgb[2]);

    // convert color space
    ret[0] = 0.4124 * rgb[0] + 0.3576 * rgb[1] + 0.1805 * rgb[2];
    ret[1] = 0.2126 * rgb[0] + 0.7152 * rgb[1] + 0.0722 * rgb[2];
    ret[2] = 0.0193 * rgb[0] + 0.1192 * rgb[1] + 0.9505 * rgb[2];

    // clamp
    ret[0] = std::clamp(ret[0], 0.f, 1.f);
    ret[1] = std::clamp(ret[1], 0.f, 1.f);
    ret[2] = std::clamp(ret[2], 0.f, 1.f);

    return ret;
  }

  XYZColor::XYZColor(const Vec3& vec) : value{vec[0], vec[1], vec[2]} {};

  const float_t& XYZColor::operator[](size_t i) const {
    return value[i];
  }

  float_t& XYZColor::operator[](size_t i) {
    return value[i];
  }

  Vec3 XYZColor::to_vec() const {
    return {x, y, z};
  }

  RGBColor XYZColor::to_rgb() const {
    return XYZToRGB(to_vec());
  }
}