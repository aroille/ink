#include "math/transform.h"
#include "math/geometry.h"

namespace ink
{
  //================================================================================
  Matrix4x4::Matrix4x4()
  {
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] =
      m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
  }

  Matrix4x4::Matrix4x4(float mat[4][4])
  {
    memcpy(m, mat, 16 * sizeof(float));
  }

  inline Matrix4x4::Matrix4x4(float t00, float t01, float t02, float t03,
    float t10, float t11, float t12, float t13,
    float t20, float t21, float t22, float t23,
    float t30, float t31, float t32, float t33)
  {
    m[0][0] = t00;
    m[0][1] = t01;
    m[0][2] = t02;
    m[0][3] = t03;
    m[1][0] = t10;
    m[1][1] = t11;
    m[1][2] = t12;
    m[1][3] = t13;
    m[2][0] = t20;
    m[2][1] = t21;
    m[2][2] = t22;
    m[2][3] = t23;
    m[3][0] = t30;
    m[3][1] = t31;
    m[3][2] = t32;
    m[3][3] = t33;
  }

  bool Matrix4x4::operator == (const Matrix4x4 &m2) const
  {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (m[i][j] != m2.m[i][j]) return false;
    return true;
  }

  bool Matrix4x4::operator != (const Matrix4x4 &m2) const
  {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (m[i][j] != m2.m[i][j]) return true;
    return false;
  }

  Matrix4x4 inverse(const Matrix4x4 &m)
  {
    int indxc[4], indxr[4];
    int ipiv[4] = { 0, 0, 0, 0 };
    float minv[4][4];
    memcpy(minv, m.m, 4 * 4 * sizeof(float));
    for (int i = 0; i < 4; i++) {
      int irow = 0, icol = 0;
      float big = 0.f;
      // Choose pivot
      for (int j = 0; j < 4; j++) {
        if (ipiv[j] != 1) {
          for (int k = 0; k < 4; k++) {
            if (ipiv[k] == 0) {
              if (std::abs(minv[j][k]) >= big) {
                big = float(std::abs(minv[j][k]));
                irow = j;
                icol = k;
              }
            }
            else if (ipiv[k] > 1)
              abort();  //("Singular matrix in MatrixInvert");
          }
        }
      }
      ++ipiv[icol];
      // Swap rows _irow_ and _icol_ for pivot
      if (irow != icol) {
        for (int k = 0; k < 4; ++k) std::swap(minv[irow][k], minv[icol][k]);
      }
      indxr[i] = irow;
      indxc[i] = icol;
      if (minv[icol][icol] == 0.f) abort();  //("Singular matrix in MatrixInvert");

      // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
      float pivinv = 1.f / minv[icol][icol];
      minv[icol][icol] = 1.;
      for (int j = 0; j < 4; j++) minv[icol][j] *= pivinv;

      // Subtract this row from others to zero out their columns
      for (int j = 0; j < 4; j++) {
        if (j != icol) {
          float save = minv[j][icol];
          minv[j][icol] = 0;
          for (int k = 0; k < 4; k++) minv[j][k] -= minv[icol][k] * save;
        }
      }
    }
    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
      if (indxr[j] != indxc[j]) {
        for (int k = 0; k < 4; k++)
          std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
      }
    }
    return Matrix4x4(minv);
  }

  Matrix4x4 transpose(const Matrix4x4 &m)
  {
    return Matrix4x4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
      m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
      m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
      m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
  }


  Transform::Transform(const float mat[4][4])
  {
    m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
      mat[1][0], mat[1][1], mat[1][2], mat[1][3],
      mat[2][0], mat[2][1], mat[2][2], mat[2][3],
      mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
    m_inv = inverse(m);
  }


  Transform::Transform(const Matrix4x4 &m)
    : m(m), m_inv(inverse(m))
  {

  }

  Transform::Transform(const Matrix4x4 &m, const Matrix4x4 &m_inv)
    : m(m), m_inv(m_inv)
  {

  }

  bool Transform::operator == (const Transform& in) const
  {
    return in.m == m && in.m_inv == m_inv;
  }

  bool Transform::operator != (const Transform& in) const
  {
    return in.m != m || in.m_inv != m_inv;
  }

  Transform Transform::operator*(const Transform &t2) const
  {
    return Transform(Matrix4x4::mul(m, t2.m), Matrix4x4::mul(t2.m_inv, m_inv));
  }

  Transform inverse(const Transform& t)
  {
    return Transform(t.m_inv, t.m);
  }

  Transform transpose(const Transform& t)
  {
    return Transform(transpose(t.m), transpose(t.m_inv));
  }

  Transform translate(float x, float y, float z)
  {
    Matrix4x4			m(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
    Matrix4x4 m_inv(1, 0, 0, -x, 0, 1, 0, -y, 0, 0, 1, -z, 0, 0, 0, 1);
    return Transform(m, m_inv);
  }

  Transform scale(float x, float y, float z)
  {
    Matrix4x4 m(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
    Matrix4x4 m_inv(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0, 0, 1);
    return Transform(m, m_inv);

  }

  Transform rotate_x(float theta)
  {
    float sinTheta = std::sin(radians(theta));
    float cosTheta = std::cos(radians(theta));
    Matrix4x4 m(1, 0, 0, 0, 0, cosTheta, -sinTheta, 0, 0, sinTheta, cosTheta, 0,
      0, 0, 0, 1);
    return Transform(m, transpose(m));
  }

  Transform rotate_y(float theta)
  {
    float sinTheta = std::sin(radians(theta));
    float cosTheta = std::cos(radians(theta));
    Matrix4x4 m(cosTheta, 0, sinTheta, 0, 0, 1, 0, 0, -sinTheta, 0, cosTheta, 0,
      0, 0, 0, 1);
    return Transform(m, transpose(m));
  }

  Transform rotate_z(float theta)
  {
    float sinTheta = std::sin(radians(theta));
    float cosTheta = std::cos(radians(theta));
    Matrix4x4 m(cosTheta, -sinTheta, 0, 0, sinTheta, cosTheta, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 1);
    return Transform(m, transpose(m));
  }

  Transform look_at(const Point3f& pos, const Point3f& target, const Vec3f& up)
  {
    float m[4][4];

    m[0][3] = pos.x;
    m[1][3] = pos.y;
    m[2][3] = pos.z;
    m[3][3] = 1;

    Vec3f dir = normalize(target - pos);
    Vec3f left = normalize(cross(normalize(up), dir));
    Vec3f newUp = cross(dir, left);

    m[0][0] = left.x;
    m[1][0] = left.y;
    m[2][0] = left.z;
    m[3][0] = 0;

    m[0][1] = newUp.x;
    m[1][1] = newUp.y;
    m[2][1] = newUp.z;
    m[3][1] = 0;

    m[0][2] = dir.x;
    m[1][2] = dir.y;
    m[2][2] = dir.z;
    m[3][2] = 0;

    return Transform(m);
  }

} // namespace ink
