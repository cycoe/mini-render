#ifndef __RENDER_BVH_HPP__
#define __RENDER_BVH_HPP__

#include "Bounds3.hpp"
#include "Intersection.hpp"
#include "Object.hpp"
#include "Ray.hpp"

struct BVHNode {
public:
  Bounds3 bounds;
  BVHNode* left;
  BVHNode* right;
  Object* object;

public:
  BVHNode(void) : left(nullptr), right(nullptr), object(nullptr) { }
};

class BVHAccelerator {
public:
  enum class SplitMethod {
    NAIVE,
    SAH
  };

public:
  Intersection intersect(Ray const& ray) const;

protected:
  Intersection get_intersection(BVHNode const* node, Ray const& ray) const;

protected:
  SplitMethod m_split_method;
  BVHNode* m_root;
};

#endif  // __RENDER_BVH_HPP__
