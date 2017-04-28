#pragma once

#include <cassert>
#include "math/vector.h"
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

    static Matrix4x4 mul(const Matrix4x4 &m1, const Matrix4x4 &m2);
    static Matrix4x4 transpose(const Matrix4x4 &m);
    static Matrix4x4 inverse(const Matrix4x4 &m);
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
  Transform look_at(const Vec3f& pos, const Vec3f& target, const Vec3f& up);
  Transform camera_look_at(const Vec3f& pos, const Vec3f& target, const Vec3f& up);

  Vec3f transform_point(const Matrix4x4 m, const Vec3f& p);
  Vec3f transform_vec(const Matrix4x4 m, const Vec3f& v);
  Ray   transform_ray(const Matrix4x4 m, const Matrix4x4 m_inv, const Ray& r);
  //================================================================================
  
  /*
  template <typename T>
  inline Normal3<T> Transform::operator()(const Normal3<T>& n) const
  {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(m_inv.m[0][0] * x + m_inv.m[1][0] * y + m_inv.m[2][0] * z,
                      m_inv.m[0][1] * x + m_inv.m[1][1] * y + m_inv.m[2][1] * z,
                      m_inv.m[0][2] * x + m_inv.m[1][2] * y + m_inv.m[2][2] * z);
  }
  */

  


} // namespace ink
