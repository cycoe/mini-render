#ifndef __RENDER_UTILS_HPP__
#define __RENDER_UTILS_HPP__

#include <algorithm>
#include <random>

constexpr float epsilon = 0.0001f;
constexpr float pi = 3.141592653589793f;

inline float deg2rad(float deg) {
  return deg * pi / 180.f;
}

template <typename _T>
inline _T clamp(_T lo, _T hi, _T v) {
  return std::max(lo, std::min(hi, v));
}

template <typename _T>
inline _T get_uniform_random(void) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<_T> dist(0.f, 1.f);
  return dist(rng);
}

#endif  // __RENDER_UTILS_HPP__
