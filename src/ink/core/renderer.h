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
    const Scene* scene;
  };

  class SimpleRenderer
  {
  public:
    uint32 spp = 1; // sample per pixel
    uint32 tile_size = 16;
    uint32 random_seed = 1234;

  public:
    SimpleRenderer();

    void start(Integrator& integrator, Scene& scene, Camera& camera, Film& film, Filter& filter);

  private:
    void thread_task();

  private:

    Integrator* integrator;
    Filter*     filter;
    Scene*      scene;
    Camera*     camera;
    Film*       film;

    uint32 tile_count;
    uint32 tile_count_x;
    uint32 tile_count_y;
    std::atomic_int32_t next_tile;
  };

}    // namespace ink

