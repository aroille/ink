#pragma once

#include "math/random.h"
#include "math/ray.h"
#include "math/vector3.h"

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
      ray_out.d = reflect(ray_in.d, hit.n) + roughness * random_in_unit_sphere(gen);

      attenuation = albedo;
    }
  };

  // DIELECTRIC
  class Dielectric : public Material
  {
  public:
    float ri = 1.3f;

  public:
    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) const override
    {
      auto schlick = [](float cosine, float ri) -> float
      {
        float r0 = (1 - ri) / (1 + ri);
        r0 = r0*r0;
        return r0 + (1 - r0)*powf(1 - cosine, 5);
      };

      auto RandomFloat01 = [](RandomGenerator& gen) -> float
      {
        return (gen() + 1)*0.5f;
      };

      ray_out.o = ray_in.o + hit.t * ray_in.d;

      Vec3f outwardN;
      Vec3f rdir = ray_in.d;

      Vec3f refl = reflect(rdir, hit.n);
      float nint;
      attenuation = Vec3f(1, 1, 1);
      Vec3f refr;
      float reflProb;
      float cosine;
      if (dot(rdir, hit.n) > 0)
      {
        outwardN = -hit.n;
        nint = ri;
        cosine = ri * dot(rdir, hit.n);
      }
      else
      {
        outwardN = hit.n;
        nint = 1.0f / ri;
        cosine = -dot(rdir, hit.n);
      }
      if (refract(rdir, outwardN, nint, refr))
      {
        reflProb = schlick(cosine, ri);
      }
      else
      {
        reflProb = 1;
      }

      if (RandomFloat01(gen) < reflProb)
        ray_out.d = normalize(refl);
      else
        ray_out.d = normalize(refr);
    }
  };

}    // namespace ink

