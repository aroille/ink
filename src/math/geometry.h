#pragma once

#include "math/normal.h"
#include "math/point.h"
#include "math/vector.h"
#include "math/ray.h"
#include "math/transform.h"

namespace ink
{

  //================================================================================
  template <typename T>
  inline Vector3<T>::Vector3(Normal3<T> const& in) : x(in.x), y(in.y), z(in.z)
  {

  }

  //================================================================================
  template <typename T>
  inline Vector3<T>::Vector3(Point3<T> const& in) : x(in.x), y(in.y), z(in.z)
  {

  }

  //================================================================================
  template <typename T>
  inline Normal3<T>::Normal3(Vector3<T> const& in) : x(in.x), y(in.y), z(in.z)
  {

  }

  //================================================================================
  template <typename T>
  inline bool near_equal(Point3<T> const& a, Point3<T> const& b, float delta)
  {
    return ink::near_equal(a.x, b.x, delta) &&
      ink::near_equal(a.y, b.y, delta) &&
      ink::near_equal(a.z, b.z, delta);
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
  inline bool near_equal(Normal3<T> const& a, Normal3<T> const& b, float delta)
  {
    return ink::near_equal(a.x, b.x, delta) &&
      ink::near_equal(a.y, b.y, delta) &&
      ink::near_equal(a.z, b.z, delta);
  }

  //================================================================================
  template <typename T>
  inline float distance(Point3<T> const& a, Point3<T> const& b)
  {
    return (a - b).length();
  }

  //================================================================================
  template <typename T>
  inline float distance_squared(Point3<T> const& a, Point3<T> const& b)
  {
    return (a - b).length_squared();
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> normalize(const Vector3<T>& in)
  {
    return in / in.length();
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> normalize(const Normal3<T>& in)
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
  inline float dot(Vector3<T> const& a, Normal3<T> const& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  //================================================================================
  template <typename T>
  inline float dot(Normal3<T> const& a, Vector3<T> const& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  //================================================================================
  template <typename T>
  inline float dot(Normal3<T> const& a, Normal3<T> const& b)
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
  inline Vector3<T> cross(Vector3<T> const& a, Normal3<T> const& b)
  {
    return Vector3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> cross(Normal3<T> const& a, Vector3<T> const& b)
  {
    return Vector3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> reflection(Vector3<T> const& in, Vector3<T> const& normal)
  {
    return in - normal * (2.f * dot(in, normal));
  }

  //================================================================================
  inline bool quadratic(float A, float B, float C, float& t0, float& t1)
  {
    float discrim = B*B - 4 * A*C;
    if (discrim <= 0)
      return false;

    float root_discrim = sqrtf(discrim);

    float q;
    if (B < 0)	q = -0.5 * (B - root_discrim);
    else				q = -0.5 * (B + root_discrim);
    t0 = q / A;
    t1 = C / q;

    if (t0 > t1)
    {
      float t = t0;
      t0 = t1;
      t1 = t;
    }
    return true;
  }

} // namespace ink
