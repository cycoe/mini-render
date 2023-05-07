#ifndef __RENDER_UTILS_HPP__
#define __RENDER_UTILS_HPP__

#include <algorithm>

constexpr float epsilon = 0.0001f;

template <typename _T>
inline _T clamp(_T lo, _T hi, _T v) {
  return std::max(lo, std::min(hi, v));
}

#endif  // __RENDER_UTILS_HPP__
