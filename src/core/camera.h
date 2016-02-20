#pragma once

#include "core/ink.h"
#include "math/geometry.h"
#include <random>

namespace ink
{
  class RandomGenerator;
  class Film;


  struct ProjectionMatrix
  {
    Transform world_to_camera;
    Transform camera_to_world;

    Transform	camera_to_screen;
    Transform screen_to_camera;

    Transform screen_to_raster;
    Transform raster_to_screen;

    Transform raster_to_camera;
  };

  struct INK_API Camera
  {
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Point3f& raster_coord, RandomGenerator& gen) = 0;
    virtual void update(const Film&) = 0;
  };

  struct INK_API PinholeCamera : public Camera
  {
    float             fov;
    Transform         transform;

  private:
    ProjectionMatrix  proj;

  public:
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Point3f& raster_coord, RandomGenerator& gen);
    virtual void update(const Film&);
  };


}	// namespace ink

