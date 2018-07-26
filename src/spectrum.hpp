#pragma once

#include <functional>
#include <array>
#include <algorithm>
#include <optional>
#include "float.hpp"
#include "geometry.hpp"
#include "CIE_XYZ.hpp"
#include "sRGB.hpp"

namespace naga::rt {

  /// \brief CoefficientSpectrum
  /// \param N Number of sample spectrum
  template <size_t N>
  class CoefficientSpectrum {
  public:
    /// Ctor
    CoefficientSpectrum() = default;
    /// Ctor
    CoefficientSpectrum(const CoefficientSpectrum&) = default;
    /// Ctor
    CoefficientSpectrum(CoefficientSpectrum&&) = default;
    /// operator=
    CoefficientSpectrum& operator=(const CoefficientSpectrum&) = default;
    /// operator=
    CoefficientSpectrum& operator=(CoefficientSpectrum&&) = default;

    /// Fill ctor
    CoefficientSpectrum(float_t v) {
      std::fill_n(m_samples.data(), N, v);
    }

    /// operator+=
    CoefficientSpectrum& operator+=(const CoefficientSpectrum& other) {
      std::transform(
        m_samples.begin(), m_samples.end(), other.m_samples.begin(),
        std::plus<float_t>());
    }
    /// operator+=
    CoefficientSpectrum& operator-=(const CoefficientSpectrum& other) {
      std::transform(
        m_samples.begin(), m_samples.end(), other.m_samples.begin(),
        std::minus<float_t>());
    }
    /// operator*=
    CoefficientSpectrum& operator*=(const CoefficientSpectrum& other) {
      std::transform(
        m_samples.begin(), m_samples.end(), other.m_samples.begin(),
        std::multiplies<float_t>());
    }
    /// operator/=
    CoefficientSpectrum& operator/=(const CoefficientSpectrum& other) {
      std::transform(
        m_samples.begin(), m_samples.end(), other.m_samples.begin(),
        std::divides<float_t>());
    }

    /// has_NaN
    bool has_NaN() const {
      for (auto&& v : m_samples)
        if (std::isnan(v)) return true;
      return false;
    }
    /// operator[]
    constexpr float& operator[](size_t n) {
      return m_samples[n];
    }
    /// operator[]
    constexpr const float& operator[](size_t n) const {
      return m_samples[n];
    }
    /// size
    constexpr size_t size() {
      return m_samples.size();
    }
    /// operator==
    friend bool operator==(
      const CoefficientSpectrum& lhs, const CoefficientSpectrum& rhs) {
      return lhs.m_samples == rhs.m_samples;
    }
    /// operator!=
    friend bool operator!=(
      const CoefficientSpectrum& lhs, const CoefficientSpectrum& rhs) {
      return lhs.m_samples != rhs.m_samples;
    }
    /// take sqrt
    friend CoefficientSpectrum sqrt(const CoefficientSpectrum& s) {
      CoefficientSpectrum ret;
      std::transform(
        s.m_samples.begin(), s.m_samples.end(), ret.begin(),
        [](auto v) { return std::sqrt(v); });
      return ret;
    }
    /// take clamp
    friend CoefficientSpectrum clamp(
      const CoefficientSpectrum& s, float_t low, float_t high) {
      CoefficientSpectrum ret;
      std::transform(
        s.m_samples.begin(), s.m_samples.end(), ret.m_samples.begin(),
        [&](auto v) { return std::clamp(v, low, high); });
      return ret;
    }

  protected:
    /// samples
    std::array<float_t, N> m_samples;
  };

  /// operator+
  template <size_t N>
  CoefficientSpectrum<N> operator+(
    const CoefficientSpectrum<N>& lhs, const CoefficientSpectrum<N>& rhs) {
    auto ret = lhs;
    return ret += rhs;
  }
  /// operator-
  template <size_t N>
  CoefficientSpectrum<N> operator-(
    const CoefficientSpectrum<N>& lhs, const CoefficientSpectrum<N>& rhs) {
    auto ret = lhs;
    return ret -= rhs;
  }
  /// operator*
  template <size_t N>
  CoefficientSpectrum<N> operator*(
    const CoefficientSpectrum<N>& lhs, const CoefficientSpectrum<N>& rhs) {
    auto ret = lhs;
    return ret *= rhs;
  }
  /// operator/
  template <size_t N>
  CoefficientSpectrum<N> operator/(
    const CoefficientSpectrum<N>& lhs, const CoefficientSpectrum<N>& rhs) {
    auto ret = lhs;
    return ret /= rhs;
  }
  /// lerp
  template <size_t N>
  CoefficientSpectrum<N> lerp(
    float_t t,
    const CoefficientSpectrum<N>& s1,
    const CoefficientSpectrum<N>& s2) {
    return (1 - t) * s1 + t * s2;
  }
  /// Take average spectrum from samples
  template <class Container>
  constexpr float_t AverageSpectrumSamples(
    const Container& samples, float_t lambdaStart, float_t lambdaEnd) {

    // no sample points
    if (samples.empty()) return 0;
    // sampels are outside of range
    if (lambdaEnd < samples.front().first) return samples.front().second;
    // samples are outside of range
    if (lambdaStart > samples.back().first) return samples.back().second;
    // single sample
    if (samples.size() == 1) return samples.front().second;

    float_t area = 0.f;

    // samples are partially inside
    if (lambdaStart < samples.front().first) {
      area += samples[0].second * (samples[0].first - lambdaStart);
    }
    // samples are partially inside
    if (samples.back().first < lambdaEnd) {
      area += samples.back().second * (lambdaEnd - samples.back().first);
    }

    // find segment
    size_t i = 0;
    while (lambdaStart > samples[i + 1].first)
      ++i;

    // no sample point inside
    if (samples[i + 1].first > lambdaEnd) {
      auto l = samples[i + 1].first - samples[i].first;
      auto p1 = lambdaStart / l;
      auto p2 = lambdaEnd / l;
      auto v1 = samples[i].second * p1 + samples[i + 1].second * (1 - p1);
      auto v2 = samples[i].second * p2 + samples[i + 1].second * (1 - p2);
      return (v1 + v2) / 2;
    }

    // interpolate samples
    auto interp = [&](float_t l, size_t i) {
      return lerp(
        (l - samples[i].first) / (samples[i + 1].first - samples[i].first),
        samples[i].second, samples[i + 1].second);
    };

    for (; i + 1 < samples.size() && samples[i].first <= lambdaEnd; ++i) {
      auto segmentS = std::max(lambdaStart, samples[i].first);
      auto segmentE = std::min(lambdaEnd, samples[i + 1].first);
      auto l1 = interp(segmentS, i);
      auto l2 = interp(segmentE, i);
      area += (l1 + l2) * (segmentE - segmentS) * 0.5;
    }

    return area / (lambdaEnd - lambdaStart);
  }

  /// Spectrum Type
  enum class SpectrumType { Reflectance, Illuminant };

  /// \brief SampledSpectrum
  /// \param Start start frequency
  /// \param End end frequency
  /// \param N number of samples
  template <
    size_t Start = 400,
    size_t End = 700,
    size_t N = 60>
  class SampledSpectrum : public CoefficientSpectrum<N> {
  public:
    // check
    static_assert(End >= Start);
    static_assert(N != 0);

    /// unit: nm
    static constexpr size_t sampleLambdaStart = Start;
    /// unit: nm
    static constexpr size_t sampleLambdaEnd = End;
    /// number of samples
    static constexpr size_t nSamples = N;

    /// Ctor
    constexpr SampledSpectrum() : CoefficientSpectrum<N>(){};
    /// Ctor
    constexpr SampledSpectrum(float_t v) : CoefficientSpectrum<N>(v) {}

    /// Initialize SampledSpectrum from samples
    SampledSpectrum(const std::vector<std::pair<float_t, float_t>>& samples) {
      auto s = samples;
      std::sort(
        s.begin(), s.end(), [](auto& l, auto& r) { return l.first < r.first; });

      for (size_t i = 0; i < N; ++i) {
        // start/end of current range
        float_t ls = (End - Start) * i / float_t(N);
        float_t le = (End - Start) * (i + 1) / float_t(N);
        this->m_samples[i] = AverageSpectrumSamples(s, ls, le);
      }
    }
    constexpr size_t lambdaStart() const {
      return sampleLambdaStart;
    }
    constexpr size_t lambdaEnd() const {
      return sampleLambdaEnd;
    }

    /// convert spectrum to XYZ coefficients with
    /// $ \frac{1}{\int{Y(\lambda)}} \frac{\lambda_{end} - \lambda_{start}}{N} \sum_0^{N-1}{X_{i}c_i} $
    Vec3 toXYZ() const;

    /// get Y
    float_t toY() const;


    /// X matching curve
    static const SampledSpectrum XCurve;
    /// Y matching curve
    static const SampledSpectrum YCurve;
    /// Z matching curve
    static const SampledSpectrum ZCurve;

    // reflective color spectrum
    static const SampledSpectrum rWhite;
    static const SampledSpectrum rCyan;
    static const SampledSpectrum rMagenta;
    static const SampledSpectrum rYellow;
    static const SampledSpectrum rRed;
    static const SampledSpectrum rGreen;
    static const SampledSpectrum rBlue;

    // illuminant color spectrum
    static const SampledSpectrum iWhite;
    static const SampledSpectrum iCyan;
    static const SampledSpectrum iMagenta;
    static const SampledSpectrum iYellow;
    static const SampledSpectrum iRed;
    static const SampledSpectrum iGreen;
    static const SampledSpectrum iBlue;

    
  };

  template <size_t N>
  constexpr std::array<std::pair<float_t, float_t>, N> spectSampleToArray(
    const float_t (&lambda)[N], const float_t (&s)[N]) {
    std::array<std::pair<float_t, float_t>, N> ret{};
    for (size_t i = 0; i < N; ++i) {
      ret[i].first = lambda[i];
      ret[i].second = s[i];
    }
    return ret;
  }

  /// XYZ utilities
  namespace CIE_XYZ {

    /// generate X/Y/Z color sample array for AverageSpectrumSamples()
    constexpr std::array<std::pair<float_t, float_t>, nSamples> getSample(
      const float_t (&s)[nSamples]) {
      return spectSampleToArray(lambda, s);
    }

    /// XYZ sample
    struct XYZSample {
      float_t lambda;
      float_t X, Y, Z;
    };

    /// generate CIESamples
    constexpr std::array<XYZSample, nSamples> getSamples() {
      std::array<XYZSample, nSamples> ret = {};
      for (size_t i = 0; i < nSamples; ++i) {
        ret[i] = {lambda[i], X[i], Y[i], Z[i]};
      }
      return ret;
    }

    /// CIE X Samples
    constexpr std::array<std::pair<float_t, float_t>, nSamples> XSamples =
      getSample(X);
    /// CIE Y Samples
    constexpr std::array<std::pair<float_t, float_t>, nSamples> YSamples =
      getSample(Y);
    /// CIE Z Samples
    constexpr std::array<std::pair<float_t, float_t>, nSamples> ZSamples =
      getSample(Z);
    /// CIE Samples
    constexpr std::array<XYZSample, nSamples> XYZSamples = getSamples();

    /// Get SampledSpectrum curve
    template <size_t Start, size_t End, size_t N, size_t NSamples>
    constexpr SampledSpectrum<Start, End, N> getCurve(
      const std::array<std::pair<float_t, float_t>, NSamples>& samples) {
      SampledSpectrum<Start, End, N> s;
      for (size_t i = 0; i < s.size(); ++i) {
        float_t l0 =
          lerp(i / float_t(s.size()), s.lambdaStart(), s.lambdaEnd());
        float_t l1 =
          lerp((i + 1) / float_t(s.size()), s.lambdaStart(), s.lambdaEnd());

        s[i] = AverageSpectrumSamples(samples, l0, l1);
      }
      return s;
    }

  } // namespace CIE_XYZ

  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::XCurve =
      CIE_XYZ::getCurve<Start, End, N>(CIE_XYZ::XSamples);
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::YCurve =
      CIE_XYZ::getCurve<Start, End, N>(CIE_XYZ::YSamples);
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::ZCurve =
      CIE_XYZ::getCurve<Start, End, N>(CIE_XYZ::ZSamples);

  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rWhite = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rWhite));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rCyan = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rCyan));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rMagenta = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rMagenta));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rYellow = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rYellow));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rRed = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rRed));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rGreen = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rGreen));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::rBlue = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::rBlue));

  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iWhite = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iWhite));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iCyan = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iCyan));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iMagenta = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iMagenta));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iYellow = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iYellow));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iRed = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iRed));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iGreen = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iGreen));
  template <size_t Start, size_t End, size_t N>
  constexpr SampledSpectrum<Start, End, N>
    SampledSpectrum<Start, End, N>::iBlue = CIE_XYZ::getCurve<Start, End, N>(
      spectSampleToArray(RGBToSpectrum::lambda, RGBToSpectrum::iBlue));

  template <size_t Start, size_t End, size_t N>
  Vec3 SampledSpectrum<Start, End, N>::toXYZ() const {
    Vec3 sum{0};
    for (size_t i = 0; i < N; ++i) {
      sum[0] += XCurve[i] * this->m_samples[i];
      sum[1] += YCurve[i] * this->m_samples[i];
      sum[2] += ZCurve[i] * this->m_samples[i];
    }

    sum[0] *= (End - Start) / float_t(N);
    sum[1] *= (End - Start) / float_t(N);
    sum[2] *= (End - Start) / float_t(N);

    sum[0] /= CIE_XYZ::sigmaX;
    sum[1] /= CIE_XYZ::sigmaY;
    sum[2] /= CIE_XYZ::sigmaZ;

    // clamp
    sum[0] = std::clamp(sum[0], 0.f, 1.f);
    sum[1] = std::clamp(sum[1], 0.f, 1.f);
    sum[1] = std::clamp(sum[2], 0.f, 1.f);

    return sum;
  }

  template <size_t Start, size_t End, size_t N>
  float_t SampledSpectrum<Start, End, N>::toY() const {
    float_t sum{};
    for (size_t i = 0; i < N; ++i) {
      sum += YCurve[i] * this->m_samples[i];
    }
    float_t scale = (End - Start) / (CIE_XYZ::sigmaY * N);
    return scale * sum;
  }
} // namespace naga::rt