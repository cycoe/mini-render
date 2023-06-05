#include "BVH.hpp"
#include "Intersection.hpp"

Intersection BVHAccelerator::intersect(const Ray &ray) const {
  if (!m_root) {
    return Intersection();
  }
  return this->get_intersection(m_root, ray);
}

Intersection BVHAccelerator::get_intersection(BVHNode const *node,
                                              Ray const &ray) const {
  if (!node->bounds.intersect_p(ray)) {
    return Intersection();
  }

  /// leaf node
  if (node->left == nullptr || node->right == nullptr) {
    return node->object->intersect(ray);
  }

  Intersection hit_left = get_intersection(node->left, ray);
  Intersection hit_right = get_intersection(node->right, ray);

  return (hit_left.coords - ray.origin).norm() <
                 (hit_right.coords - ray.origin).norm()
             ? hit_left
             : hit_right;
}
