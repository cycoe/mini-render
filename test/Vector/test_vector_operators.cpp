#include "Vector.hpp"
#include <algorithm>
#include <cassert>

constexpr float epsilon = 0.0001f;

void test_vector_binary_op(void) {
  Vector3<float> vec_a(1.f, 2.f, 3.f);
  Vector3<float> vec_b(1.f, 2.f, 3.f);
  Vector3<float> ret_add = vec_a + vec_b;
  Vector3<float> ret_sub = vec_a - vec_b;
  Vector3<float> ret_mul = vec_a * vec_b;
  Vector3<float> ret_div = vec_a / vec_b;
  assert(ret_add.x == 2.f && ret_add.y == 4.f && ret_add.z == 6.f);
  assert(ret_sub.x == 0.f && ret_sub.y == 0.f && ret_sub.z == 0.f);
  assert(ret_mul.x == 1.f && ret_mul.y == 4.f && ret_mul.z == 9.f);
  assert(ret_div.x == 1.f && ret_div.y == 1.f && ret_div.z == 1.f);
}

void test_vector_binary_op_scalar(void) {
  Vector3<float> vec_a(1.f, 2.f, 3.f);
  float scalar = 2.f;
  Vector3<float> ret_add = vec_a + scalar;
  Vector3<float> ret_sub = vec_a - scalar;
  Vector3<float> ret_mul = vec_a * scalar;
  Vector3<float> ret_div = vec_a / scalar;
  assert(ret_add.x == 3.f && ret_add.y == 4.f && ret_add.z == 5.f);
  assert(ret_sub.x == -1.f && ret_sub.y == 0.f && ret_sub.z == 1.f);
  assert(ret_mul.x == 2.f && ret_mul.y == 4.f && ret_mul.z == 6.f);
  assert(ret_div.x == 0.5f && ret_div.y == 1.f && ret_div.z == 1.5f);
}

void test_vector_norm(void) {
  Vector3<float> vec(1.f, -2.f, 3.f);
  float norm = vec.norm();
  assert(norm - std::sqrt(14.f) < epsilon);
}

void test_vector_normalized(void) {
  Vector3<float> vec(1.f, -2.f, 3.f);
  Vector3<float> vec_normalized = vec.normalized();
  float norm = vec.norm();
  assert(vec_normalized.x - 1.f / norm < epsilon);
  assert(vec_normalized.y - (-2.f) / norm < epsilon);
  assert(vec_normalized.z - 3.f / norm < epsilon);
}

void test_vector_dot_product(void) {
  Vector3<float> vec_a(1.f, 2.f, 3.f);
  Vector3<float> vec_b(2.f, 3.f, 4.f);
  float dot = dot_product(vec_a, vec_b);
  assert(dot - 20.f < epsilon);
}

void test_vector_cross_product(void) {
  Vector3<float> vec_a(1.f, 2.f, 3.f);
  Vector3<float> vec_b(2.f, 3.f, 4.f);
  Vector3<float> cross = cross_product(vec_a, vec_b);
  assert(cross.x - (-1.f) < epsilon);
  assert(cross.y - 2.f < epsilon);
  assert(cross.z - (-1.f) < epsilon);
}

int main(void) {
  test_vector_binary_op();
  test_vector_binary_op_scalar();
  test_vector_norm();
  test_vector_normalized();
  test_vector_dot_product();
  test_vector_cross_product();
}
