#ifndef __RENDER_MATERIAL_HPP__
#define __RENDER_MATERIAL_HPP__

#include "Vector.hpp"
#include "Utils.hpp"

inline Vector3f reflect(Vector3f const &I, Vector3f const &N) {
  return I - 2 * dot_product(I, N) * N;
}

// Compute refraction direction using Snell's law
//
// We need to handle with care the two possible situations:
//
//    - When the ray is inside the object
//
//    - When the ray is outside.
//
// If the ray is outside, you need to make cosi positive cosi = -N.I
//
// If the ray is inside, you need to invert the refractive indices and negate
// the normal N
//
// Caution: I must be normalized, R returned is already normalized
inline Vector3f refract(Vector3f const &I, Vector3f const &N, float ior) {
  float cosi = clamp(-1.f, 1.f, dot_product(I, N));
  float etai = 1.f, etat = ior;
  Vector3f n = N;
  if (cosi < 0) {
    cosi = -cosi;
  } else {
    std::swap(etai, etat);
    n = -N;
  }
  float eta = etai / etat;
  float k = 1 - eta * eta * (1 - cosi * cosi);
  return k < 0 ? Vector3f(0.f) : eta * I + (eta * cosi - std::sqrt(k)) * n;
}

// Compute Fresnel equation
//
// \param I is the incident view direction
//
// \param N is the normal at the intersection point
//
// \param ior is the material refractive index
//
// \param[out] kr is the amount of light reflected

inline float fresnel(Vector3f const &I, Vector3f const &N, float ior) {
  float cosi = clamp(-1.f, 1.f, dot_product(I, N));
  float etai = 1.f, etat = ior;
  if (cosi > 0.f) {
    std::swap(etai, etat);
  }
  /// Compute sini using Snell's law
  float sint = etai / etat * std::sqrt(std::max(0.f, 1 - cosi * cosi));
  /// Total internal reflection
  if (sint >= 1.f) {
    return 1.f;
  } else {
    float cost = std::sqrt(std::max(0.f, 1 - sint * sint));
    cosi = std::fabs(cosi);
    float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
    float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
    return (Rs * Rs + Rp * Rp) / 2;
  }
}

class Material {
public:
  virtual Vector3f sample(Vector3f const& wo, Vector3f const& n) = 0;
  virtual float pdf(Vector3f const& wi, Vector3f const& wo, Vector3f const& n) = 0;
  virtual Vector3f eval(Vector3f const& wi, Vector3f const& wo, Vector3f const& n) = 0;

  inline bool has_emission(void) const;
  inline Vector3f get_emission(void) const;

protected:
  Vector3f m_emission;
};

bool Material::has_emission(void) const { return m_emission.norm() > epsilon; }

Vector3f Material::get_emission(void) const { return m_emission; }

#endif  // __RENDER_MATERIAL_HPP__
