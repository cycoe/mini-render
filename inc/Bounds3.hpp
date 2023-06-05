#ifndef __RENDER_BOUNDS3_HPP__
#define __RENDER_BOUNDS3_HPP__

#include "Ray.hpp"
#include "Vector.hpp"
#include <cstddef>
#include <limits>

enum class Axis { X = 0, Y, Z };

struct Bounds3 {
public:
  Vector3f p_min;
  Vector3f p_max;

public:
  inline Bounds3(void)
      : p_max(std::numeric_limits<float>::lowest()),
        p_min(std::numeric_limits<float>::max()) {}
  inline Bounds3(Vector3f const &p) : p_min(p), p_max(p) {}
  inline Bounds3(Vector3f const &p1, Vector3f const &p2)
      : p_min(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y),
              std::fmin(p1.z, p2.z)),
        p_max(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y),
              std::fmax(p1.z, p2.z)) {}

  inline Vector3f diagonal(void) const { return p_max - p_min; }

  inline Axis max_extent(void) const {
    Vector3f d = this->diagonal();
    if (d.x > d.y && d.x > d.z) {
      return Axis::X;
    } else if (d.y > d.z) {
      return Axis::Y;
    } else {
      return Axis::Z;
    }
  }

  inline Vector3f centroid(void) const { return 0.5f * (p_min + p_max); }

  inline Bounds3 operator&(Bounds3 const& b) const;
  inline Bounds3 operator|(Bounds3 const& b) const;
  inline Bounds3 operator|(Vector3f const& p) const;

  inline bool intersect_p(Ray const& ray) const;
};

Bounds3 Bounds3::operator&(Bounds3 const &b) const {
  return Bounds3(Vector3f::max(this->p_min, b.p_min),
                 Vector3f::min(this->p_max, b.p_max));
}

Bounds3 Bounds3::operator|(Bounds3 const &b) const {
  return Bounds3(Vector3f::min(this->p_min, b.p_min),
                 Vector3f::max(this->p_max, b.p_max));
}

Bounds3 Bounds3::operator|(Vector3f const &p) const {
  return Bounds3(Vector3f::min(this->p_min, p),
                 Vector3f::max(this->p_max, p));
}

bool Bounds3::intersect_p(const Ray &ray) const {
  float t_enter = -std::numeric_limits<float>::infinity();
  float t_exit  = std::numeric_limits<float>::infinity();
  Vector3f direction_inv = 1.f / ray.direction;
  for (std::size_t axis = 0; axis < 3; ++axis) {
    float t_min = (p_min[axis] - ray.origin[axis]) * direction_inv[axis];
    float t_max = (p_max[axis] - ray.origin[axis]) * direction_inv[axis];
    if (ray.direction[axis] < 0.f) {
      std::swap(t_min, t_max);
    }
    t_enter = std::fmax(t_min, t_enter);
    t_exit  = std::fmax(t_max, t_exit);
  }

  return t_enter <= t_exit && t_exit >= 0;
}

#endif // __RENDER_BOUNDS3_HPP__
