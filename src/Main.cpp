#include "Camera.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
#include <memory>


int main(int argc, char *argv[]) {
  Vector3f camera_pos(250.f, 250.f, -800.f);
  Vector3f camera_front(0.f, 0.f, 1.f);
  Vector3f camera_up(0.f, 1.f, 0.f);
  auto camera = std::make_unique<Camera>(768, 768, 40, camera_pos, camera_front, camera_up);
  Scene scene;
  scene.add(std::move(camera));
  Renderer renderer("example");
  renderer.render(scene, 1024);

  return 0;
}
