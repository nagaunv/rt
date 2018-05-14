#pragma once

#include <type_traits>
#include "image.hpp"

namespace naga::rt {

  /// Renderer
  class Renderer {
  public:
    /// Render image
    virtual void render(Image& img) const = 0;
    /// Dtor
    virtual ~Renderer() {}

  protected:
    Renderer() = default;
  };

  /// PixelRenderer
  template <class T>
  class PixelRenderer {
  protected:
    PixelRenderer() = default;

  private:
    /// Check if T has valid constructor
    void _check_constructor() {
      static_assert(
        std::is_same_v<
          T, decltype(
               T(std::shared_ptr<Scene>(), 
                 std::shared_ptr<Camera>(), 
                 PixelLength(),
                 PixelLength()))>,
        "T does not satisfy PixelRenderer requirements");
    }
    /// Check if T has valid render()
    void _check_render() {
      // Pixel render(PixelIndex x, PixelIndex y) const;
      static_assert(
        std::is_same_v<
          Pixel,
          decltype(std::declval<const T>().render(PixelLength(), PixelLength()))>,
        "T does not satisfy PixelRenderer requirements");
    }

    template <auto _T>
    struct _concept_check {};
    using _render_concept_check = _concept_check<&_check_render>;
    using _constructor_concept_check = _concept_check<&_check_constructor>;
  };
}