#pragma once

#include "math/random.h"
#include "math/ray.h"
#include "math/vector.h"
namespace ink
{
  inline Vec3f random_in_unit_sphere(RandomGenerator& gen)
  {
    Vec3f p;
    do
    {
      p = Vec3f(gen(), gen(), gen());
    } while (p.length_squared() >= 1.0);
    return p;
  }

  class Material
  {
  public:
    Vec3f emission = Vec3f::zero;

  public:
    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) const = 0;
  };

  // LAMBERT
  class Lambertian : public Material
  {
  public:
    Vec3f albedo = Vec3f(0.7f, 0.7f, 0.7f);
  
  public:
    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) const override
    { 
      ray_out.o = ray_in.o + hit.t * ray_in.d;
      ray_out.d = hit.n + random_in_unit_sphere(gen);

      attenuation = albedo;
    }
  };

  // METAL
  class Metal : public Material
  {
  public:
    Vec3f albedo = Vec3f(0.7f, 0.7f, 0.7f);
    float roughness = 0.02f;

  public:
    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) const override
    {
      ray_out.o = ray_in.o + hit.t * ray_in.d;
      ray_out.d = reflection(ray_in.d, hit.n) + roughness * random_in_unit_sphere(gen);

      attenuation = albedo;
    }
  };

}    // namespace ink

