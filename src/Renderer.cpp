#include "Renderer.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "Scene.hpp"
#include "Utils.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstdio>
#include <functional>
#include <vector>
#include <thread>

static void render_thread(Renderer::FramebufferC &framebuffer,
                          Scene const &scene, Camera const& camera,
                          std::size_t spp, unsigned y_s, unsigned y_e) {
  for (std::size_t k = 0; k < spp; ++k) {
    for (unsigned x = 0; x < camera.width(); ++x) {
      for (unsigned y = y_s; y < y_e; ++y) {
        framebuffer[Index2D{x, y}] += scene.cast_ray(camera.ray_to_panel(x, y));
      }
    }
  }
}

Renderer::Renderer(std::string const& project_name)
  :m_project_name(project_name) {}

void Renderer::render(const Scene &scene, std::size_t spp) const {
  Camera const* camera = scene.get_actived_camera();
  if (camera == nullptr) {
    return;
  }

  FramebufferC framebuffer(camera->width(), camera->height());

  unsigned num_workers = std::thread::hardware_concurrency();
  unsigned num_lines = camera->height() / num_workers + 1;
  std::vector<std::thread> workers;
  for (unsigned i = 0; i < num_workers; ++i) {
    unsigned y_s = i * num_lines;
    unsigned y_e = std::min<int>(y_s + num_lines, camera->height());
  }
}

void Renderer::dump(const FramebufferC &framebuffer, const std::string &file_name) const {
  FILE* fp = fopen(file_name.c_str(), "wb");
  std::size_t width = framebuffer.width();
  std::size_t height = framebuffer.height();
  (void)fprintf(fp, "P6\n%d %d\n255\n", static_cast<int>(width), static_cast<int>(height));
  for (std::size_t i = 0; i < width * height; ++i) {
    static unsigned char color[3];
    color[0] = (unsigned char)(255 * std::pow(clamp(0.f, 1.f, framebuffer[i].x), 0.6f));
    color[1] = (unsigned char)(255 * std::pow(clamp(0.f, 1.f, framebuffer[i].y), 0.6f));
    color[2] = (unsigned char)(255 * std::pow(clamp(0.f, 1.f, framebuffer[i].z), 0.6f));
    fwrite(color, 1, 3, fp);
  }
  fclose(fp);
}
