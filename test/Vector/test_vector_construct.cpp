#include <cassert>
#include "Vector.hpp"

void test_default_construct(void) {
  Vector3<float> vec;
  assert(vec.x == 0 && vec.y == 0 && vec.z == 0);
}

void test_one_value_construct(void) {
  Vector3<float> vec(1.f);
  assert(vec.x == 1.f && vec.y == 1.f && vec.z == 1.f);
}

void test_normal_construct(void) {
  Vector3<float> vec(1.f, 2.f, 3.f);
  assert(vec.x == 1.f && vec.y == 2.f && vec.z == 3.f);
}

void test_copy_construct(void) {
  Vector3<float> vec_a{1.f, 2.f, 3.f};
  Vector3<float> vec_b(vec_a);
  assert(vec_b.x == 1.f && vec_b.y == 2.f && vec_b.z == 3.f);
}

int main(void) {
  test_default_construct();
  test_one_value_construct();
  test_normal_construct();
}
