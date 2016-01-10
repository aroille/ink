#pragma once

#include "core/ink.h"

namespace ink
{
  template <typename T>
  struct Vector3;

  template <typename T>
  struct Normal3
  {
    // Attributes
    T x, y, z;

    // Static constants
    static const Normal3<T> zero;
    static const Normal3<T> unit_x;
    static const Normal3<T> unit_y;
    static const Normal3<T> unit_z;
    static const Normal3<T> one;

    // Methods
    Normal3() = default;
    Normal3(Normal3<T> const& in) = default;
    Normal3(T x_val, T y_val, T z_val);
    explicit Normal3(Vector3<T> const& in);

    Normal3<T> operator-() const;
    Normal3<T> operator+(Normal3<T> const& in) const;
    Normal3<T> operator-(Normal3<T> const& in) const;
    Normal3<T> operator*(T f) const;
    Normal3<T> operator/(T f) const;

    Normal3<T>& operator+=(Normal3<T> const& in);
    Normal3<T>& operator-=(Normal3<T> const& in);
    Normal3<T>& operator*=(T f);
    Normal3<T>& operator/=(T f);

    T operator[](int i) const;
    T& operator[](int i);

    float	length() const;
    float	length_squared() const;
  };

  typedef Normal3<float>	Normal3f;


  //================================================================================
  template<typename T>
  const Normal3<T> Normal3<T>::zero = Normal3<T>(0, 0, 0);

  template<typename T>
  const Normal3<T> Normal3<T>::unit_x = Normal3<T>(1, 0, 0);

  template<typename T>
  const Normal3<T> Normal3<T>::unit_y = Normal3<T>(0, 1, 0);

  template<typename T>
  const Normal3<T> Normal3<T>::unit_z = Normal3<T>(0, 0 1);

  template<typename T>
  const Normal3<T> Normal3<T>::one = Normal3<T>(1, 1, 1);


  //================================================================================
  template <typename T>
  inline Normal3<T>::Normal3(T x_value, T y_value, T z_val) : x(x_value), y(y_value), z(z_val)
  {

  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Normal3<T>::operator-() const
  {
    return Normal3<T>(-x, -y, -z);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Normal3<T>::operator+(Normal3<T> const& in) const
  {
    return Normal3<T>(x + in.x, y + in.y, z + in.z);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Normal3<T>::operator-(Normal3<T> const& in) const
  {
    return Normal3<T>(x - in.x, y - in.y, z - in.z);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Normal3<T>::operator*(T f) const
  {
    return Normal3<T>(x * f, y * f, z * f);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Normal3<T>::operator/	(T f) const
  {
    float inv = 1.0f / f;
    return Normal3<T>(x * inv, y * inv, z * inv);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T>& Normal3<T>::operator+=(Normal3 const& in)
  {
    x += in.x;
    y += in.y;
    z += in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Normal3<T>& Normal3<T>::operator-=(Normal3<T> const& in)
  {
    x -= in.x;
    y -= in.y;
    z -= in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Normal3<T>& Normal3<T>::operator*=(T f)
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Normal3<T>& Normal3<T>::operator/=(T f)
  {
    float inv = 1.0f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> operator*(T f, const Normal3<T>& v)
  {
    return v*f;
  }

  //================================================================================
  template <typename T>
  inline T Normal3<T>::operator[](int i) const
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline T& Normal3<T>::operator[](int i)
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline float Normal3<T>::length() const
  {
    return sqrt(length_squared());
  }

  //================================================================================
  template <typename T>
  inline float Normal3<T>::length_squared() const
  {
    return x*x + y*y + z*z;
  }

} // namespace ink
