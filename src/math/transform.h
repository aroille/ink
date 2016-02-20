#pragma once

#include "core/ink.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/ray.h"

namespace ink
{
  struct Matrix4x4
  {
    // Attributes
    float m[4][4];

    // Methods
    Matrix4x4();
    Matrix4x4(float mat[4][4]);
    Matrix4x4(float t00, float t01, float t02, float t03,
      float t10, float t11, float t12, float t13,
      float t20, float t21, float t22, float t23,
      float t30, float t31, float t32, float t33);

    bool operator==(const Matrix4x4 &m2) const;
    bool operator!=(const Matrix4x4 &m2) const;

    static Matrix4x4 mul(const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
      Matrix4x4 r;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          r.m[i][j] = m1.m[i][0] * m2.m[0][j]
          + m1.m[i][1] * m2.m[1][j]
          + m1.m[i][2] * m2.m[2][j]
          + m1.m[i][3] * m2.m[3][j];
      return r;
    }
  };

  class Transform
  {
  public:
    Transform() {}
    Transform(const float mat[4][4]);
    Transform(const Matrix4x4& m);
    Transform(const Matrix4x4& m, const Matrix4x4& m_inv);

    bool              operator==(const Transform& in) const;
    bool              operator!=(const Transform& in) const;
    Transform         operator*(const Transform &t2) const;

    const Matrix4x4&  matrix() const { return m; }
    const Matrix4x4&  inverse_matrix() const { return m_inv; }

    template <typename T>
    inline Point3<T>  operator()(const Point3<T>&) const;

    template <typename T>
    inline Vector3<T> operator()(const Vector3<T>&) const;

    template <typename T>
    inline Normal3<T> operator()(const Normal3<T>&) const;

    inline Ray        operator()(const Ray&) const;

    friend Transform inverse(const Transform& t);
    friend Transform transpose(const Transform& t);

  private:
    Matrix4x4 m;
    Matrix4x4 m_inv;
  };

  Transform translate(float x, float y, float z);
  Transform scale(float x, float y, float z);
  Transform rotate_x(float theta);
  Transform rotate_y(float theta);
  Transform rotate_z(float theta);
  Transform look_at(const Point3f& pos, const Point3f& target, const Vec3f& up);

  //================================================================================
  template <typename T>
  inline Point3<T> Transform::operator()(const Point3<T>& p) const
  {
    T x = p.x, y = p.y, z = p.z;
    T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
    if (wp == 0) abort();
    if (wp == 1)
      return Point3<T>(xp, yp, zp);
    else
      return Point3<T>(xp, yp, zp) / wp;
  }

  //================================================================================
  template <typename T>
  inline Vector3<T> Transform::operator()(const Vector3<T>& v) const
  {
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                      m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                      m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
  }

  //================================================================================
  template <typename T>
  inline Normal3<T> Transform::operator()(const Normal3<T>& n) const
  {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(m_inv.m[0][0] * x + m_inv.m[1][0] * y + m_inv.m[2][0] * z,
                      m_inv.m[0][1] * x + m_inv.m[1][1] * y + m_inv.m[2][1] * z,
                      m_inv.m[0][2] * x + m_inv.m[1][2] * y + m_inv.m[2][2] * z);
  }

  inline Ray Transform::operator()(const Ray& r) const
  {
    Ray ray = r;
    ray.o = (*this)(r.o);
    ray.d = (*this)(r.d);
    return ray;
  }


} // namespace ink
