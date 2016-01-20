#pragma once

#include "core/ink.h"
#include "math/geometry.h"
#include <random>

namespace ink
{
  class RandomGenerator;

  class INK_API Camera
  {
  public:
    Camera();
    void      generate_ray(uint32 x, uint32 y, Ray& ray, RandomGenerator& gen);
    void      update_transforms();

  public:
    float     fov;
    Transform transform;
    uint32    film_width;
    uint32    film_height;
    float     screen_window[4];

  public:
    Transform world_to_camera;
    Transform camera_to_world;

    Transform	camera_to_screen;
    Transform screen_to_camera;

    Transform screen_to_raster;
    Transform raster_to_screen;

    Transform raster_to_camera;
  };

}	// namespace ink

