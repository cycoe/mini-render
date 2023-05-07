#ifndef __RENDER_RAY_HPP__
#define __RENDER_RAY_HPP__

#include <limits>
#include <iostream>
#include "Vector.hpp"

struct Ray {
  Vector3f origin;
  Vector3f direction;
  double t;
  double t_min;
  double t_max;

  Ray(Vector3f const& _origin, Vector3f const& _direction, double const _t = 0.0)
    : origin(_origin)
    , direction(_direction)
    , t(_t)
    , t_min(0.0)
    , t_max(std::numeric_limits<double>::infinity()) { }

  Vector3f operator()(double t) const { return origin + direction * t; }
};

#endif  // __RENDER_RAY_HPP__
