#pragma once

#include "math/common.h"
#include "math/random.h"
#include "math/vector.h"
#include <atomic>

namespace ink
{
  class Camera;
  class Film;
  class Filter;
  struct Scene;
  struct Ray;

  class Integrator
  {
  public:
    virtual Vec3f radiance(const Ray& ray, RandomGenerator& gen) const = 0;
    Scene* scene;
  };

  class SimpleIntegrator : public Integrator
  {
  public:
    virtual Vec3f radiance(const Ray& ray, RandomGenerator& gen) const ;
  };

  class SimpleRenderer
  {
  public:
    uint32 spp = 1; // sample per pixel
    uint32 tile_size = 16;

  public:
    SimpleRenderer();
    ~SimpleRenderer();
    void start(Integrator& integrator, Scene& scene, Camera& camera, Film& film);

  private:
    void thread_task();

  private:

    Integrator* integrator;
    Filter*     filter;
    Scene*      scene;
    Camera*     camera;
    Film*       film;

    RandomGenerator prim_generator;
    RandomGenerator diffuse_generator;

    uint32 tile_count;
    uint32 tile_count_x;
    uint32 tile_count_y;
    std::atomic_int32_t next_tile;
  };

}    // namespace ink

