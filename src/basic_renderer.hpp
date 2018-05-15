#pragma once


#include <range/v3/all.hpp>
#include <memory>
#include <thread>
#include <functional>
#include <type_traits>

#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "renderer.hpp"

namespace naga::rt {

  /// Basic renderer
  template <class PixelRendererType>
  class BasicRenderer : Renderer {
  public:
    /// Ctor
    BasicRenderer(
      const std::shared_ptr<Scene>& scene,
      const std::shared_ptr<Camera>& camera,
      std::size_t n_threads,
      std::size_t n_subimage_x,
      std::size_t n_subimage_y)
      : m_scene{scene}
      , m_camera{camera}
      , m_n_threads{n_threads}
      , m_n_subimage_x{n_subimage_x}
      , m_n_subimage_y{n_subimage_y} {}

    /// Render image
    virtual void render(Image& img) const override {
      // render:
      //  1. Devide image into subimages
      //  2. Create pixel renderer
      //  3. Call render function for each subimages(possibly multi-threaded)
      //  4. join rendered subimages
      //  6. return control

      const glm::tvec2<std::size_t> subimage_delta = {
        img.width() / m_n_subimage_x, img.height() / m_n_subimage_y};

      // initialize pixel renderer
      PixelRendererType pixel_renderer(
        m_scene, m_camera, img.width(), img.height());

      // render tasks
      std::deque<std::function<void()>> tasks;

      // set tasks
      for (auto&& sub_x : ranges::view::ints({0}, m_n_subimage_x)) {
        for (auto&& sub_y : ranges::view::ints({0}, m_n_subimage_y)) {
          // set subimage position
          auto subimage_pos = subimage_delta;
          subimage_pos.x *= sub_x;
          subimage_pos.y *= sub_y;

          // set subimage size
          auto subimage_size = subimage_delta;
          // extend subimage to cover edge
          if (sub_x == m_n_subimage_x)
            subimage_size.x = img.width() - subimage_pos.x;
          if (sub_y == m_n_subimage_y)
            subimage_size.y = img.height() - subimage_pos.y;

          // push tasks
          tasks.push_back([=, &img, &pixel_renderer]() {
            for (std::size_t sx = 0; sx < subimage_size.x; ++sx) {
              for (std::size_t sy = 0; sy < subimage_size.y; ++sy) {
                auto x = PixelIndex(sx + subimage_pos.x);
                auto y = PixelIndex(sy + subimage_pos.y);
                assert(x < img.width() && y < img.height());
                img(x, y) = pixel_renderer.render(x, y);
              }
            }
            return;
          });
        }
      }

      // threads
      std::vector<std::thread> threads;
      // task queue mutex
      std::mutex tq_mtx;

      // create threads
      for (auto nt : ranges::view::ints({0}, m_n_threads)) {
        threads.emplace_back([&, nt]() {
          while (true) {
            std::function<void()> task;
            { // lock task queue
              std::lock_guard<std::mutex> lock(tq_mtx);
              if (tasks.empty()) return;
              task = tasks.front();
              tasks.pop_front();
            }
            // execute task
            task();
          }
        });
      }

      // join threads
      for (auto& t : threads)
        t.join();
    }

    /// Dtor
    virtual ~BasicRenderer() {}

  private:
    /// Scene
    std::shared_ptr<Scene> m_scene;
    /// Camera
    std::shared_ptr<Camera> m_camera;
    /// Number of thread
    std::size_t m_n_threads;
    /// Number of subimages in width
    std::size_t m_n_subimage_x;
    /// Number of subimage in height
    std::size_t m_n_subimage_y;
  };
}