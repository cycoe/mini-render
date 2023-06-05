#ifndef __RENDER_INTERSECTION_HPP__
#define __RENDER_INTERSECTION_HPP__

#include "Vector.hpp"

class Object;

struct Intersection {
public:
  Intersection(void) : happened(false), coords(), normal(), object(nullptr) {}

public:
  bool happened;
  Vector3f coords;
  Vector3f normal;
  Object *object;
};

#endif // __RENDER_INTERSECTION_HPP__
