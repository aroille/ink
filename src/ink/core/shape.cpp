
#include "core/shape.h"
#include "math/common.h"
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

} // namespace ink