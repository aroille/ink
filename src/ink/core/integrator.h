#pragma once

#include "math/common.h"
#include "math/vector3.h"
#include <atomic>

namespace ink
{
  struct Scene;
  struct Ray;
  class RandomGenerator;

  struct RenderStats
  {
    std::atomic<uint32> rayCount;
  };

  //! Integrator abstract class
  class Integrator
  {
  public:
    virtual Vec3f trace(const Ray& ray, RandomGenerator& gen, RenderStats& stats) const = 0;
  public:
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
    virtual Vec3f trace(const Ray& ray, RandomGenerator& gen, RenderStats& stats) const;

  private:
    Vec3f trace(const Ray& ray, RandomGenerator& gen, int remaining_bounce, RenderStats& stats) const;
  };

  //! Debug integrator that can easily access:
  //! - OpenMP thread id
  //! - Primary hit infos
  class DebugIntegrator : public Integrator
  {
  public:
    virtual Vec3f trace(const Ray& ray, RandomGenerator& gen, RenderStats& stats) const;
  };

}    // namespace ink

