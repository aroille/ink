#pragma once

#include "math/common.h"
#include "math/vector.h"

namespace ink
{
  struct Scene;
  struct Ray;
  class RandomGenerator;

  //! Integrator abstract class
  class Integrator
  {
  public:
    virtual Vec3f radiance(const Ray& ray, RandomGenerator& gen) const = 0;
    const Scene* scene;
  };

  //! Simple integrator, multiple bounce, emissive materials and sky only
  //! (no light sampling, no importance sampling)
  class SimpleIntegrator : public Integrator
  {
  public:
    uint32 max_bounce = 3;
    Vec3f sky_radiance = Vec3f(0.7f, 0.7f, 0.7f);

  public:
    virtual Vec3f radiance(const Ray& ray, RandomGenerator& gen) const;

  private:
    Vec3f radiance(const Ray& ray, RandomGenerator& gen, int remaining_bounce) const;
  };

  //! Debug integrator that can easily access:
  //! - OpenMP thread id
  //! - Primary hit infos
  class DebugIntegrator : public Integrator
  {
  public:
    virtual Vec3f radiance(const Ray& ray, RandomGenerator& gen) const;
  };

}    // namespace ink

