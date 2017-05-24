#pragma once

#include <cmath>

namespace ink
{
  template <typename T>
  struct Vector2
  {
    // Attributes
    T x, y;

    // Static constants
    static const Vector2<T> zero;
    static const Vector2<T> unit_x;
    static const Vector2<T> unit_y;
    static const Vector2<T> one;

    // Methods
    Vector2() = default;
    Vector2(Vector3<T> const& in) = default;
    Vector2(T x_val, T y_val);

    Vector2<T>  operator-() const;
    Vector2<T>  operator+(Vector3<T> const& in) const;
    Vector2<T>  operator-(Vector3<T> const& in) const;
    Vector2<T>  operator*(T f) const;
    Vector2<T>  operator*(Vector3<T> const& in) const;
    Vector2<T>  operator/(T f) const;

    Vector2<T>& operator+=(Vector3<T> const& in);
    Vector2<T>& operator-=(Vector3<T> const& in);
    Vector2<T>& operator*=(T f);
    Vector2<T>& operator/=(T f);

    T           operator[](int i) const;
    T&          operator[](int i);

    float	      length() const;
    float	      length_squared() const;
  };

  typedef Vector2<int>	Vec2i;

  //================================================================================
  template<typename T>
  const Vector2<T> Vector3<T>::zero = Vector3<T>(0, 0);

  template<typename T>
  const Vector2<T> Vector2<T>::unit_x = Vector3<T>(1, 0);

  template<typename T>
  const Vector2<T> Vector3<T>::unit_y = Vector3<T>(0, 1);

  template<typename T>
  const Vector2<T> Vector3<T>::one = Vector3<T>(1, 1);

  //================================================================================
  template <typename T>
  inline Vector2<T>::Vector2(T x_value, T y_value) : x(x_value), y(y_value)
  {

  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator-() const
  {
    return Vector2<T>(-x, -y);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator+(Vector2<T> const& in) const
  {
    return Vector2<T>(x + in.x, y + in.y);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator-(Vector2<T> const& in) const
  {
    return Vector2<T>(x - in.x, y - in.y);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator*(T f) const
  {
    return Vector2<T>(x * f, y * f);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator*(Vector2<T> const& in) const
  {
    return Vector2<T>(x * in.x, y * in.y);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> Vector2<T>::operator/	(T f) const
  {
    float inv = 1.0f / f;
    return Vector2<T>(x * inv, y * inv);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T>& Vector2<T>::operator+=(Vector2 const& in)
  {
    x += in.x;
    y += in.y;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& in)
  {
    x -= in.x;
    y -= in.y;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector2<T>& Vector2<T>::operator*=(T f)
  {
    x *= f;
    y *= f;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector2<T>& Vector2<T>::operator/=(T f)
  {
    float inv = 1.0f / f;
    x *= inv;
    y *= inv;
    return *this;
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> operator*(T f, const Vector2<T>& v)
  {
    return v*f;
  }

  //================================================================================
  template <typename T>
  inline T Vector2<T>::operator[](int i) const
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline T& Vector2<T>::operator[](int i)
  {
    return (&x)[i];
  }

  //================================================================================
  template <typename T>
  inline float Vector2<T>::length() const
  {
    return sqrt(length_squared());
  }

  //================================================================================
  template <typename T>
  inline float Vector2<T>::length_squared() const
  {
    return x*x + y*y;
  }

  //================================================================================
  template <typename T>
  inline bool near_equal(Vector2<T> const& a, Vector2<T> const& b, float delta)
  {
    return ink::near_equal(a.x, b.x, delta) &&
      ink::near_equal(a.y, b.y, delta);
  }

  //================================================================================
  template <typename T>
  inline Vector2<T> normalize(const Vector2<T>& in)
  {
    return in / in.length();
  }

} // namespace ink
