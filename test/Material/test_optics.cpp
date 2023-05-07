#include <cassert>
#include "Material.hpp"
#include "Vector.hpp"
#include "Utils.hpp"

void test_reflect_outside(void) {
  Vector3f I(1.f, 1.f, -1.f);
  Vector3f N(0.f, 0.f, 1.f);
  Vector3f O = reflect(I, N);
  assert(O.x - 1.f < epsilon && O.y - 1.f < epsilon && O.z - 1.f < epsilon);
}

void test_reflect_inside(void) {
  Vector3f I(1.f, 1.f, 1.f);
  Vector3f N(0.f, 0.f, 1.f);
  Vector3f O = reflect(I, N);
  assert(O.x - 1.f < epsilon && O.y - 1.f < epsilon && O.z - (-1.f) < epsilon);
}

void test_refract_from_outside(void) {
  Vector3f I = Vector3f(1.f, 1.f, -1.f).normalized();
  Vector3f N(0.f, 0.f, 1.f);
  float ior = 1.5f;
  Vector3f R = refract(I, N, ior);
  Vector3f expected = Vector3f(1.f, 1.f, -std::sqrt(19.f) / 2).normalized();
  assert(R.x - expected.x < epsilon && R.y - expected.y < epsilon &&
         R.z - expected.z < epsilon);
}

void test_refract_from_inside(void) {
  Vector3f I = Vector3f(1.f, 1.f, std::sqrt(19.f) / 2).normalized();
  Vector3f N(0.f, 0.f, 1.f);
  float ior = 1.5f;
  Vector3f R = refract(I, N, ior);
  Vector3f expected = Vector3f(1.f, 1.f, 1.f).normalized();
  assert(R.x - expected.x < epsilon && R.y - expected.y < epsilon &&
         R.z - expected.z < epsilon);
}

void test_refract_with_small_ior(void) {
  Vector3f I = Vector3f(1.f, 1.f, -std::sqrt(19.f) / 2).normalized();
  Vector3f N(0.f, 0.f, 1.f);
  float ior = 1.f / 1.5f;
  Vector3f R = refract(I, N, ior);
  Vector3f expected = Vector3f(1.f, 1.f, -1.f).normalized();
  assert(R.x - expected.x < epsilon && R.y - expected.y < epsilon &&
         R.z - expected.z < epsilon); 
}

int main(void) {
  test_reflect_outside();
  test_reflect_inside();
  test_refract_from_outside();
  test_refract_from_inside();
  test_refract_with_small_ior();
  return 0;
}
