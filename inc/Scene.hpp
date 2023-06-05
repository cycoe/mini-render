#ifndef __RENDER_SCENE_HPP__
#define __RENDER_SCENE_HPP__

#include <vector>
#include <memory>
#include "BVH.hpp"
#include "Camera.hpp"
#include "Intersection.hpp"
#include "Object.hpp"
#include "Ray.hpp"

class Scene {
public:
  using Cameras = std::vector<std::unique_ptr<Camera>>;
  using Objects = std::vector<std::unique_ptr<Object>>;

public:
  Scene(void);

public:
  Scene& add(std::unique_ptr<Camera>&& camera);
  Scene& add(std::unique_ptr<Object>&& object);
  Scene& active_camera(Cameras::size_type actived_camera);
  Camera const* get_actived_camera(void) const;
  Scene& build_bvh(void);
  Intersection intersect(Ray const& ray) const;
  void sample_light(Intersection& pos, float& pdf) const;
  Vector3f shade(Intersection const& shade_point, Vector3f const& wo) const;
  Vector3f cast_ray(Ray const& ray) const;

protected:
  float m_russian_roulette;

  Cameras m_cameras;
  Objects m_objects;
  Cameras::size_type m_actived_camera;
  std::unique_ptr<BVHAccelerator> m_bvh;
};

#endif // __RENDER_SCENE_HPP__
