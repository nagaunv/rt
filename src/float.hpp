#pragma once
#include <limits>

namespace naga::rt {
  static_assert(std::numeric_limits<float>::is_iec559);
  static_assert(std::numeric_limits<double>::is_iec559);
  static_assert(std::numeric_limits<long double>::is_iec559);

  /// define float_t
  using float_t = float;
}