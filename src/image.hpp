#pragma once

#include <cstdint>
#include <cstdlib>

#include <selene/img/Image.hpp>

/// \file Import image classes

namespace naga::rt {
  /// Image
  using Image = sln::Image<sln::Pixel_8u3>;
  /// Pixel
  using Pixel = Image::PixelType;
  /// PixelIndex
  using PixelIndex = sln::PixelIndex;
  /// PixelLength
  using PixelLength = sln::PixelLength;
}