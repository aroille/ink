#pragma once

#include "core/ink.h"
#include "math/geometry.h"
#include "math/random.h"
#include <vector>
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
    Material() : emission(Vec3f::zero) {}

    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) = 0;

    Vec3f emission;
  };

  // LAMBERT
  class LambertMaterial : public Material
  {
  public:
    LambertMaterial(Vec3f albedo) : Material(), albedo(albedo) {}

    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) override
    {
      ray_out.o = ray_in.o + hit.t * (1.0f - hit.epsilon) * ray_in.d;
      ray_out.d = normalize(Vec3f(hit.n) + random_in_unit_sphere(gen));

      attenuation = albedo;
    }

    Vec3f albedo;
  };

  // METAL
  class MetalMaterial : public Material
  {
  public:
    MetalMaterial(Vec3f albedo, float roughness = 0.0f) : Material(), albedo(albedo), roughness(roughness){}

    virtual void scatter(const Ray& ray_in, const RayHit& hit, Ray& ray_out, Vec3f& attenuation, RandomGenerator& gen) override
    {
      ray_out.o = ray_in.o + hit.t * (1.0f - hit.epsilon) * ray_in.d;
      ray_out.d = normalize(reflection(ray_in.d, Vec3f(hit.n)) + roughness*random_in_unit_sphere(gen));

      attenuation = albedo;
    }

    Vec3f albedo;
    float roughness;
  };

}    // namespace ink

