#include "Scene.hpp"
#include "BVH.hpp"
#include "Intersection.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include "Vector.hpp"
#include <memory>

Scene::Scene(void) : m_russian_roulette(0.8), m_actived_camera(0) { }

Scene &Scene::add(std::unique_ptr<Camera>&& camera) {
  this->m_cameras.emplace_back(std::move(camera));
  return *this;
}

Scene &Scene::add(std::unique_ptr<Object>&& object) {
  this->m_objects.emplace_back(std::move(object));
  return *this;
}

Scene &Scene::active_camera(Cameras::size_type actived_camera) {
  if (actived_camera < m_cameras.size()) {
    m_actived_camera = actived_camera;
  }
  return *this;
}

Camera const *Scene::get_actived_camera(void) const {
  if (m_actived_camera < m_cameras.size()) {
    return m_cameras[m_actived_camera].get();
  }
  return nullptr;
}

Scene &Scene::build_bvh(void) {
  this->m_bvh = std::make_unique<BVHAccelerator>();
  return *this;
}

Intersection Scene::intersect(const Ray &ray) const {
  return this->m_bvh->intersect(ray);
}

void Scene::sample_light(Intersection &pos, float &pdf) const {
  float emit_area_sum = 0.f;
  /// calculate sum of all emit area
  for (std::unique_ptr<Object> const& obj : m_objects) {
    if (obj->has_emit()) {
      emit_area_sum += obj->get_area();
    }
  }

  /// choose an object to sample
  float p = get_uniform_random<float>();
  emit_area_sum = 0.f;
  for (std::unique_ptr<Object> const& obj : m_objects) {
    if (obj->has_emit()) {
      emit_area_sum += obj->get_area();
      if (p < emit_area_sum) {
        obj->sample(pos, pdf);
        break;
      }
    }
  }
}

Vector3f Scene::shade(const Intersection &shade_point,
                      const Vector3f &wo) const {
  /// shade on a glowing object, we just return emission
  if (shade_point.object->has_emission()) {
    return shade_point.object->get_emission();
  }

  /// direct illumination
  Vector3f lo_dir;
  {
    Intersection hit_light;
    float light_pdf;
    this->sample_light(hit_light, light_pdf);
    Vector3f obj2light = hit_light.coords - shade_point.coords;
    Vector3f obj2light_dir = obj2light.normalized();

    /// check if ray is maksed by other objects
    Ray ray(shade_point.coords, obj2light_dir);
    Intersection maybe_masked = this->intersect(ray);
    if ((maybe_masked.coords - shade_point.coords).norm() > -epsilon) {
      Material* material = shade_point.object->get_material();
      Vector3f f_r = material->eval(obj2light_dir, wo, shade_point.normal);

      float r2 = dot_product(obj2light, obj2light);
      float cos_a = std::fabs(dot_product(shade_point.normal, obj2light_dir));
      float cos_b = std::fmax(0.f, dot_product(hit_light.normal, -obj2light_dir));

      lo_dir = hit_light.object->get_emission() * f_r * cos_a * cos_b / r2 / light_pdf;
    }
  }

  /// indirect illumination
  Vector3f lo_indir;
  {
    if (get_uniform_random<float>() < m_russian_roulette) {
      Material* material = shade_point.object->get_material();
      Vector3f obj2next = material->sample(wo, shade_point.normal);
      float pdf = material->pdf(wo, obj2next, shade_point.normal);
      if (pdf > epsilon) {
        Intersection hit_next = this->intersect(Ray(shade_point.coords, obj2next));
        /// skip glowing object here
        if (hit_next.happened && !hit_next.object->has_emission()) {
          Vector3f f_r = material->eval(obj2next, wo, shade_point.normal);
          float cos = std::fabs(dot_product(obj2next, shade_point.normal));
          lo_indir = this->shade(hit_next, -obj2next) * f_r * cos / pdf / m_russian_roulette;
        }
      }
    }
  }

  return lo_dir + lo_indir;
}

Vector3f Scene::cast_ray(const Ray &ray) const {
  Intersection hit_obj = this->intersect(ray);
  return hit_obj.happened ? this->shade(hit_obj, -ray.direction) : Vector3f(0.f);
}
