#pragma once

#include "core/ink.h"
#include "math/vector.h"

namespace ink
{
  template <typename T>
  struct Point3
  {
    // Attributes
    T x, y, z;

    // Static constants
    static const Point3<T> zero;
    static const Point3<T> unit_x;
    static const Point3<T> unit_y;
    static const Point3<T> unit_z;
    static const Point3<T> one;

    // Methods
    Point3() = default;
    Point3(Point3 const& in) = default;
    Point3(float x_val, float y_val, float z_val);

    Point3<T> operator-() const;
    Point3<T> operator+(Point3<T> const& in) const;
    Point3<T> operator+(Vector3<T> const& in) const;
    Vector3<T> operator-(Point3<T> const& in) const;
    Point3<T> operator-(Vector3<T> const& in) const;
    Point3<T> operator*(T f) const;
    Point3<T> operator/(T f) const;

    Point3<T>& operator+=(Point3<T> const& in);
    Point3<T>& operator+=(Vector3<T> const& in);
    Point3<T>& operator-=(Vector3<T> const& in);
    Point3<T>& operator*=(T f);
    Point3<T>& operator/=(T f);

    T operator[](int i) const;
    T& operator[](int i);
  };

  typedef Point3<float> Point3f;
  typedef Point3<int>		Point3i;


  //================================================================================
  template<typename T>
  const Point3<T> Point3<T>::zero = Point3<T>(0, 0, 0);

  template<typename T>
  const Point3<T> Point3<T>::unit_x = Point3<T>(1, 0, 0);

  template<typename T>
  const Point3<T> Point3<T>::unit_y = Point3<T>(0, 1, 0);

  template<typename T>
  const Point3<T> Point3<T>::unit_z = Point3<T>(0, 0 1);

  template<typename T>
  const Point3<T> Point3<T>::one = Point3<T>(1, 1, 1);


  //================================================================================
  template <typename T>
  inline Point3<T>::Point3(float x_value, float y_value, float z_val) : x(x_value), y(y_value), z(z_val)
  {

  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator-() const
  {
    return Point3<T>(-x, -y, -z);
  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator+(Point3<T> const& in) const
  {
    return Point3<T>(x + in.x, y + in.y, z + in.z);
  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator+(Vector3<T> const& in) const
  {
    return Point3<T>(x + in.x, y + in.y, z + in.z);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Point3<T>::operator-(Point3<T> const& in) const
  {
    return Vector3<T>(x - in.x, y - in.y, z - in.z);
  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator-(Vector3<T> const& in) const
  {
    return Point3<T>(x - in.x, y - in.y, z - in.z);
  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator*(T f) const
  {
    return Point3<T>(x * f, y * f, z * f);
  }

  //================================================================================
  template <typename T>
  inline Point3<T> Point3<T>::operator/	(T f) const
  {
    float inv = 1.0f / f;
    return Point3<T>(x * inv, y * inv, z * inv);
  }

  //================================================================================
  template <typename T>
  inline Point3<T>& Point3<T>::operator+=(Point3<T> const& in)
  {
    x += in.x;
    y += in.y;
    z += in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Point3<T>& Point3<T>::operator+=(Vector3<T> const& in)
  {
    x += in.x;
    y += in.y;
    z += in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Point3<T>& Point3<T>::operator-=(Vector3<T> const& in)
  {
    x -= in.x;
    y -= in.y;
    z -= in.z;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Point3<T>& Point3<T>::operator*=(T f)
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Point3<T>& Point3<T>::operator/=(T f)
  {
    float inv = 1.0f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Point3<T> operator*(T f, const Point3<T>& v)
  {
    return v*f;
  }

  //================================================================================
  template <typename T>
  inline T Point3<T>::operator[](int i) const
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline T& Point3<T>::operator[](int i)
  {
    return (&x)[i];
  }

} // namespace ink
