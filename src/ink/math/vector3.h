#pragma once

#include <cmath>

namespace ink
{
  template <typename T>
  struct Vector3
  {
    // Attributes
    T x, y, z, w;

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

  //================================================================================
  template<typename T>
  const Vector3<T> Vector3<T>::zero = Vector3<T>(0, 0, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_x = Vector3<T>(1, 0, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_y = Vector3<T>(0, 1, 0);

  template<typename T>
  const Vector3<T> Vector3<T>::unit_z = Vector3<T>(0, 0, 1);

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

  //================================================================================
  template <typename T>
  inline bool near_equal(Vector3<T> const& a, Vector3<T> const& b, float delta)
  {
    return ink::near_equal(a.x, b.x, delta) &&
      ink::near_equal(a.y, b.y, delta) &&
      ink::near_equal(a.z, b.z, delta);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> normalize(const Vector3<T>& in)
  {
    return in / in.length();
  }

  //================================================================================
  template <typename T>
  inline float dot(Vector3<T> const& a, Vector3<T> const& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> cross(Vector3<T> const& a, Vector3<T> const& b)
  {
    return Vector3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> reflection(Vector3<T> const& in, Vector3<T> const& normal)
  {
    return in - normal * (2.f * dot(in, normal));
  }

} // namespace ink
