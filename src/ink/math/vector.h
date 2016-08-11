#pragma once

#include "core/ink.h"

namespace ink
{
  template <typename T>
  struct Normal3;

  template <typename T>
  struct Point3;

  template <typename T>
  struct Vector3
  {
    // Attributes
    T x, y, z;

    // Static constants
    static const Vector3<T> zero;
    static const Vector3<T> unit_x;
    static const Vector3<T> unit_y;
    static const Vector3<T> unit_z;
    static const Vector3<T> one;

    // Methods
    Vector3() = default;
    Vector3(Vector3<T> const& in) = default;
    Vector3(T x_val, T y_val, T z_val);
    explicit Vector3(Normal3<T> const& in);
    explicit Vector3(Point3<T> const& in);

    Vector3<T>  operator-() const;
    Vector3<T>  operator+(Vector3<T> const& in) const;
    Vector3<T>  operator-(Vector3<T> const& in) const;
    Vector3<T>  operator*(T f) const;
    Vector3<T>  operator*(Vector3<T> const& in) const;
    Vector3<T>  operator/(T f) const;

    Vector3<T>& operator+=(Vector3<T> const& in);
    Vector3<T>& operator-=(Vector3<T> const& in);
    Vector3<T>& operator*=(T f);
    Vector3<T>& operator/=(T f);

    T           operator[](int i) const;
    T&          operator[](int i);

    float	      length() const;
    float	      length_squared() const;
  };


  typedef Vector3<float>	Vec3f;
  typedef Vector3<int>		Vec3i;

  //================================================================================
  template<typename T>
  const Vector3<T> Vector3<T>::zero = Vector3<T>(0, 0, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_x = Vector3<T>(1, 0, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_y = Vector3<T>(0, 1, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_z = Vector3<T>(0, 0 1);

  template<typename T>
  const Vector3<T> Vector3<T>::one = Vector3<T>(1, 1, 1);

  //================================================================================
  template <typename T>
  inline Vector3<T>::Vector3(T x_value, T y_value, T z_val) : x(x_value), y(y_value), z(z_val)
  {

  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator-() const
  {
    return Vector3<T>(-x, -y, -z);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator+(Vector3<T> const& in) const
  {
    return Vector3<T>(x + in.x, y + in.y, z + in.z);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator-(Vector3<T> const& in) const
  {
    return Vector3<T>(x - in.x, y - in.y, z - in.z);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator*(T f) const
  {
    return Vector3<T>(x * f, y * f, z * f);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator*(Vector3<T> const& in) const
  {
    return Vector3<T>(x * in.x, y * in.y, z * in.z);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Vector3<T>::operator/	(T f) const
  {
    float inv = 1.0f / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T>& Vector3<T>::operator+=(Vector3 const& in)
  {
    x += in.x;
    y += in.y;
    z += in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T>& Vector3<T>::operator-=(Vector3<T> const& in)
  {
    x -= in.x;
    y -= in.y;
    z -= in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T>& Vector3<T>::operator*=(T f)
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T>& Vector3<T>::operator/=(T f)
  {
    float inv = 1.0f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> operator*(T f, const Vector3<T>& v)
  {
    return v*f;
  }

  //================================================================================
  template <typename T>
  inline T Vector3<T>::operator[](int i) const
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline T& Vector3<T>::operator[](int i)
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline float Vector3<T>::length() const
  {
    return sqrt(length_squared());
  }

  //================================================================================
  template <typename T>
  inline float Vector3<T>::length_squared() const
  {
    return x*x + y*y + z*z;
  }

} // namespace ink
