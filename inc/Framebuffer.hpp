#ifndef __RENDER_FRAMEBUFFER_HPP__
#define __RENDER_FRAMEBUFFER_HPP__

#include <cstddef>
#include <vector>

struct Index2D {
  std::size_t x;
  std::size_t y;
};

template<typename _T>
struct Framebuffer {
public:
  inline Framebuffer(std::size_t width, std::size_t height);
  inline _T& operator[](Index2D index);
  inline _T const& operator[](Index2D index) const;
  inline _T& operator[](std::size_t index);
  inline _T const& operator[](std::size_t index) const;
  inline std::size_t width(void) const;
  inline std::size_t height(void) const;

protected:
  std::size_t m_width;
  std::size_t m_height;
  std::vector<_T> m_data;
};

template <typename _T>
Framebuffer<_T>::Framebuffer(std::size_t width, std::size_t height)
    : m_width(width), m_height(height), m_data(width * height) {}

template <typename _T>
_T &Framebuffer<_T>::operator[](Index2D index) {
  return m_data[index.y * m_width + index.x];
}

template <typename _T>
_T const &Framebuffer<_T>::operator[](Index2D index) const {
  return m_data[index.y * m_width + index.x];
}

template <typename _T>
_T &Framebuffer<_T>::operator[](std::size_t index) {
  return m_data[index];
}

template <typename _T>
_T const &Framebuffer<_T>::operator[](std::size_t index) const {
  return m_data[index];
}

template <typename _T>
std::size_t Framebuffer<_T>::width(void) const {
  return m_width;
}

template <typename _T>
std::size_t Framebuffer<_T>::height(void) const {
  return m_height;
}

#endif  // __RENDER_FRAMEBUFFER_HPP__
