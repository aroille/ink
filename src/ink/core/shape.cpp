
#include "core/shape.h"
#include "math/ray.h"

namespace ink
{
  bool Sphere::intersect(const Ray& ray, RayHit& hit) const
  {
    const float A = dot(ray.d, ray.d);
    const float B = 2.0f * dot(ray.o, ray.d);
    const float C = dot(ray.o, ray.o) - radius*radius;

    float t0, t1;
    if (!quadratic(A, B, C, t0, t1))
      return false;

    if ((t0 > ray.tmin) & (t0 < ray.tmax))
    {
      hit.t = t0;
      hit.epsilon = hit.t * 5e-4f;
      hit.n = ray.o + ray.d * t0;
      return true;
    }

    if ((t1 > ray.tmin) & (t1 < ray.tmax))
    {
      hit.t = t1;
      hit.epsilon = hit.t * 5e-4f;
      hit.n = ray.o + ray.d * t1;
      return true;
    }

    return false;
  }

  bool TriangleMesh::intersect(const Ray& ray, RayHit& hit) const
  {
    hit.t = FLT_MAX;

    for (uint32 i = 0; i < tri_count; ++i)
    {
      const uint32 index1 = indices[i * 3];
      const uint32 index2 = indices[i * 3 + 1];
      const uint32 index3 = indices[i * 3 + 2];
      
      const Vec3f& p1 = vertices[index1];
      const Vec3f& p2 = vertices[index2];
      const Vec3f& p3 = vertices[index3];
      
      const Vec3f e1 = p2 - p1;
      const Vec3f e2 = p3 - p1;
      const Vec3f s1 = cross(ray.d, e2);

      const float divisor = dot(s1, e1);

      if (divisor == 0.f)
        continue;

      float inv_divisor = 1.f / divisor;

      // Compute first barycentric coordinate
      Vec3f s = ray.o - p1;
      float b1 = dot(s, s1) * inv_divisor;
      if (b1 < 0. || b1 > 1.)
        continue;

      // Compute second barycentric coordinate
      Vec3f s2 = cross(s, e1);
      float b2 = dot(ray.d, s2) * inv_divisor;
      if (b2 < 0. || b1 + b2 > 1.)
        continue;

      // Compute _t_ to intersection point
      float t = dot(e2, s2) * inv_divisor;
      if (t < ray.tmin || t > ray.tmax)
        continue;

      if (t < hit.t)
      {
        hit.t = t;
        hit.n = cross(e1, e2);
      }
    }

    hit.epsilon = hit.t * 1e-3f;
    return (hit.t != FLT_MAX);
  }

} // namespace ink