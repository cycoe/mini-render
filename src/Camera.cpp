#include "Camera.hpp"
#include "Utils.hpp"
#include "Vector.hpp"
#include <limits>

Camera::Camera(int width, int height, float fov)
    : m_width(width), m_height(height), m_fov(fov), m_aperture(0.f),
      m_focal_length(std::numeric_limits<float>::infinity()) {}

Camera::Camera(int width, int height, float fov, Vector3f const pos,
               Vector3f const &front, Vector3f const &up)
    : m_width(width), m_height(height), m_fov(fov), m_aperture(0.f),
      m_focal_length(std::numeric_limits<float>::infinity()), m_position(pos),
      m_front(front.normalized()), m_up(up.normalized()),
      m_right(cross_product(m_front, m_up)) {}

Camera &Camera::set_position(const Vector3f &position) {
  this->m_position = position;
  return *this;
}

Camera &Camera::set_front(const Vector3f &front) {
  this->m_front = front.normalized();
  this->m_right = cross_product(m_front, m_up);
  return *this;
}

Camera &Camera::set_up(const Vector3f &up) {
  this->m_up = up.normalized();
  this->m_right = cross_product(m_front, m_up);
  return *this;
}

Camera &Camera::set_lens(float aperture, float focal_length) {
  this->m_aperture = aperture;
  this->m_focal_length = focal_length;
  return *this;
}

Camera &Camera::unset_lens(void) {
  this->m_aperture = 0.f;
  this->m_focal_length = std::numeric_limits<float>::infinity();
  return *this;
}

Ray Camera::ray_to_panel(int x, int y) const {
  float scale = std::tan(deg2rad(this->m_fov * 0.5));
  float aspect_ratio = static_cast<float>(this->m_width) / this->m_height;
  float pixel_offset_h = (2 * (x + get_uniform_random<float>()) / (float)m_width - 1) * aspect_ratio * scale;
  float pixel_offset_v = (1 - 2 * (y + get_uniform_random<float>()) / (float)m_height) * scale;
  float lens_offset_h = (2 * get_uniform_random<float>() - 1) * this->m_aperture;
  float lens_offset_v = (2 * get_uniform_random<float>() - 1) * this->m_aperture;
  Vector3f dir_to_pixel = this->m_front + pixel_offset_h * this->m_right + pixel_offset_v * this->m_up;
  Vector3f focal_point = this->m_focal_length * dir_to_pixel.normalized();
  Vector3f lens_point = lens_offset_h * this->m_right + lens_offset_v * this->m_up;
  return Ray(this->m_position, (focal_point - lens_point).normalized());
}
