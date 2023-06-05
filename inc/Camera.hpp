#ifndef __RENDER_CAMERA_HPP__
#define __RENDER_CAMERA_HPP__

#include "Ray.hpp"
#include "Vector.hpp"

class Camera {
public:
  Camera(int width, int height, float fov);
  Camera(int width, int height, float fov,
         Vector3f const pos, Vector3f const& front, Vector3f const& up);
  Camera(Camera const&) = default;

  Camera& set_position(Vector3f const& position);
  Camera& set_front(Vector3f const& front);
  Camera& set_up(Vector3f const& up);
  Camera& set_lens(float aperture, float focal_length);
  Camera& unset_lens(void);
  Ray ray_to_panel(int x, int y) const;

  inline int width(void) const { return m_width; }
  inline int height(void) const { return m_height; }
  inline float fov(void) const { return m_fov; }
  inline Vector3f position(void) const { return m_position; }
  inline Vector3f front(void) const { return m_front; }
  inline Vector3f up(void) const { return m_up; }
  inline Vector3f right(void) const { return m_right; }

protected:
  int m_width;
  int m_height;
  float m_fov;
  float m_aperture;
  float m_focal_length;

  Vector3f m_position;
  Vector3f m_front;
  Vector3f m_up;
  Vector3f m_right;
};

#endif  // __RENDER_CAMERA_HPP__
