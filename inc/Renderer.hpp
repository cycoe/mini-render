#ifndef __RENDER_RENDERER_HPP__
#define __RENDER_RENDERER_HPP__

#include "Framebuffer.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

class Renderer {
public:
  using Color = Vector3f;
  using FramebufferC = Framebuffer<Color>;

public:
  Renderer(std::string const& project_name = "mini-renderer");

  void render(Scene const& scene, std::size_t spp) const;
  void dump(FramebufferC const& framebuffer, std::string const& file_name) const;

protected:
  std::string m_project_name;
};

#endif  // __RENDER_RENDERER_HPP__
