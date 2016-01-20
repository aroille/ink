
#include "core/shape.h"

namespace ink
{
  bool Sphere::intersect(const Ray& ray, RayHit& hit) const
  {
    float A = ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z;
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
    float C = ray.o.x * ray.o.x + ray.o.y * ray.o.y +
              ray.o.z * ray.o.z - radius*radius;

    float t0, t1;
    if (!quadratic(A, B, C, t0, t1))
      return false;

    if (t1 < 0.0)
      return false;

    float thit = t0;
    if (t0 < 0.0)
      thit = t1;

    hit.p = ray.o + ray.d * thit;
    hit.n = normalize(Normal3f(hit.p - Point3f(0,0,0)));

    if (dot(ray.d, hit.n) > 0.0)
      hit.n = -hit.n;

    return true;
  }

} // namespace ink