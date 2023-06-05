#ifndef __RENDER_OBJECT_HPP__
#define __RENDER_OBJECT_HPP__

#include "Intersection.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object {
public:
  Object(void) : m_material(nullptr) { }
  Object(Material* material) : m_material(material) { }

public:
  virtual Intersection intersect(Ray const& ray) const = 0;
  virtual bool has_emit(void) const = 0;
  virtual float get_area(void) const = 0;
  virtual void sample(Intersection& pos, float& pdf) const = 0;

  Material* get_material(void) const { return m_material; }
  inline bool has_emission(void) const;
  inline Vector3f get_emission(void) const;

protected:
  Material* m_material;
};

bool Object::has_emission(void) const {
  return m_material && m_material->has_emission();
}

Vector3f Object::get_emission(void) const {
  return m_material ? m_material->get_emission() : Vector3f();
}

#endif  // __RENDER_OBJECT_HPP__
