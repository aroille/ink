#pragma once

#include "math/common.h"
#include "math/vector3.h"
#include <atomic>

namespace ink
{
  class Camera;
  class Film;
  struct Scene;
  struct Ray;
  class ReconstructionFilter;
  class Integrator;

  class SimpleRenderer
  {
  public:
    uint32 spp          = 1;
    uint32 tile_size    = 16;
    uint32 random_seed  = 1234;

  public:
    void start(Integrator& integrator, Scene& scene, Camera& camera, Film& film, ReconstructionFilter& filter);

  private:
    void thread_task();

  private:
    Integrator*                integrator;
    ReconstructionFilter*      filter;
    Scene*                     scene;
    Camera*                    camera;
    Film*                      film;

    uint32                     tile_count;
    uint32                     tile_count_x;
    uint32                     tile_count_y;
    std::atomic<std::uint32_t> next_tile;
  };

}    // namespace ink

