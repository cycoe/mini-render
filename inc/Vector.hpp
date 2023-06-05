#ifndef __RENDER_VECTOR_HPP__
#define __RENDER_VECTOR_HPP__

#include <functional>
#include <cmath>

template <typename _T> class Vector3 {
public:
  _T x, y, z;

  using BinaryOp_t = std::function<_T(const _T&, const _T&)>;

  Vector3(void) : x(0), y(0), z(0) { }
  Vector3(_T v) : x(v), y(v), z(v) { }
  Vector3(_T _x, _T _y, _T _z) : x(_x), y(_y), z(_z) { }
  Vector3(Vector3<_T> const& rhs) = default;

  static Vector3<_T> min(Vector3<_T> const& v1, Vector3<_T> const& v2);
  static Vector3<_T> max(Vector3<_T> const& v1, Vector3<_T> const& v2);

  inline Vector3<_T> binary_op(Vector3<_T> const& rhs, BinaryOp_t op) const;
  inline Vector3<_T> binary_op_scalar(_T s, BinaryOp_t op) const;
  inline Vector3<_T> operator+(Vector3<_T> const& rhs) const;
  inline Vector3<_T> operator-(Vector3<_T> const& rhs) const;
  inline Vector3<_T> operator*(Vector3<_T> const& rhs) const;
  inline Vector3<_T> operator/(Vector3<_T> const& rhs) const;
  inline Vector3<_T> operator*(_T s) const;
  inline Vector3<_T> operator/(_T s) const;
  inline Vector3<_T> operator-(void) const;
  inline Vector3<_T>& operator+=(Vector3<_T> const& rhs);
  inline _T operator[](std::size_t axis) const;

  template<std::size_t _Axis>
  inline _T get(void) const;

  inline _T norm(void) const;
  inline Vector3<_T> normalized(void) const;
};

template <typename _T>
Vector3<_T> Vector3<_T>::min(const Vector3<_T> &v1, const Vector3<_T> &v2) {
  return Vector3<_T>(std::fmin(v1.x, v2.x), std::fmin(v1.y, v2.y), std::fmin(v1.z, v2.z));
}

template <typename _T>
Vector3<_T> Vector3<_T>::max(const Vector3<_T> &v1, const Vector3<_T> &v2) {
  return Vector3<_T>(std::fmax(v1.x, v2.x), std::fmax(v1.y, v2.y), std::fmax(v1.z, v2.z));
}

template <typename _T>
Vector3<_T> Vector3<_T>::binary_op(const Vector3<_T> &rhs, BinaryOp_t op) const {
  return {op(x, rhs.x), op(y, rhs.y), op(z, rhs.z)};
}

template <typename _T>
Vector3<_T> Vector3<_T>::binary_op_scalar(_T s, BinaryOp_t op) const {
  return {op(x, s), op(y, s), op(z, s)};
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator+(const Vector3<_T> &rhs) const {
  return this->binary_op(rhs, std::plus<_T>());
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator-(const Vector3<_T> &rhs) const {
  return this->binary_op(rhs, std::minus<_T>());
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator*(const Vector3<_T> &rhs) const {
  return this->binary_op(rhs, std::multiplies<_T>());
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator/(const Vector3<_T> &rhs) const {
  return this->binary_op(rhs, std::divides<_T>());
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator*(_T s) const {
  return this->binary_op_scalar(s, std::multiplies<_T>());
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator/(_T s) const {
  return this->binary_op_scalar(s, std::divides<_T>());
}

template <typename _T>
Vector3<_T> operator*(_T s, Vector3<_T> const &v) {
  return v.binary_op_scalar(s, std::multiplies<_T>());
}

template <typename _T> Vector3<_T> operator/(_T s, const Vector3<_T> &v) {
  return Vector3<_T>(s / v.x, s / v.y, s / v.z);
}

template <typename _T>
Vector3<_T> Vector3<_T>::operator-(void) const {
  return {-x, -y, -z};
}

template <typename _T>
Vector3<_T> &Vector3<_T>::operator+=(const Vector3<_T> &rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}

template <typename _T> _T Vector3<_T>::operator[](std::size_t axis) const {
  return (&x)[axis];
}

template <typename _T>
_T Vector3<_T>::norm(void) const {
  return std::sqrt(x * x + y * y + z * z);
}

template <typename _T>
template <std::size_t _Axis>
_T Vector3<_T>::get(void) const {
  static_assert(_Axis < 3, "");
  return _Axis == 0 ? x : _Axis == 1 ? y : z;
}

template <typename _T>
Vector3<_T> Vector3<_T>::normalized(void) const {
  return *this / this->norm();
}

template <typename _T>
inline _T dot_product(Vector3<_T> const &a, Vector3<_T> const &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename _T>
inline Vector3<_T> cross_product(Vector3<_T> const &a, Vector3<_T> const &b) {
  return Vector3<_T>(
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x);
}

template <typename _Stream, typename _T>
inline _Stream &operator<<(_Stream &os, Vector3<_T> const &v) {
  return os << "[" << v.x << "," << v.y << "," << v.z << "]";
}

using Vector3f = Vector3<float>;

#endif  // __RENDER_VECTOR_HPP__
