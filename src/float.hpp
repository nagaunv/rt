#pragma once
#include <limits>

namespace naga::rt {
  static_assert(std::numeric_limits<float>::is_iec559);
  static_assert(std::numeric_limits<double>::is_iec559);
  static_assert(std::numeric_limits<long double>::is_iec559);

  /// define float_t
  using float_t = float;

  /// fma
  template <class FP>
  constexpr FP fma(FP x, FP y, FP z) {
    return x * y + z;
  }

  /// fnma
  template <class FP>
  constexpr FP fnma(FP x, FP y, FP z) {
    return -(x * y + z);
  }
  /// fms
  template <class FP>
  constexpr FP fms(FP x, FP y, FP z) {
    return x * y - z;
  }
  /// fnms
  template <class FP>
  constexpr FP fnms(FP x, FP y, FP z) {
    return -(x * y - z);
  }

  /// lerp
  template <class FP, class V0, class V1>
  constexpr FP lerp(FP t, V0 v0, V1 v1) {
    //  vfnmadd213ss    xmm1, xmm0, xmm1
    //  vfmadd213ss     xmm0, xmm2, xmm1
    return fma(
      t, static_cast<FP>(v1),
      fnms(t, static_cast<FP>(v0), static_cast<FP>(v0)));
  }
}