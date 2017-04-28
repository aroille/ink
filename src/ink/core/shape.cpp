
#include "core/shape.h"
#include "math/common.h"
#include "math/ray.h"

namespace ink
{
  bool Sphere::intersect(const Ray& ray, RayHit& hit) const
  {
    float A = dot(ray.d, ray.d);
    float B = 2 * dot(ray.d, Vec3f(ray.o));
    float C = dot(Vec3f(ray.o), Vec3f(ray.o)) - radius*radius;

    float t0, t1;
    if (!quadratic(A, B, C, t0, t1))
      return false;

    if (t1 <= 0.0)
      return false;

    float thit = t0;
    if (t0 <= 0.0)
      thit = t1;

    hit.t = thit;
    hit.n = normalize(Vec3f(ray.o + ray.d * thit));

    if (dot(ray.d, hit.n) > 0.0)
      hit.n = -hit.n;

    return true;
  }

} // namespace ink