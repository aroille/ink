#pragma once

#include "core/ink.h"
#include "math/transform.h"
#include "math/point.h"
#include "math/ray.h"

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

  struct ICamera
  {
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Point3f& raster_coord, RandomGenerator& gen) = 0;
    virtual void update(const Film&) = 0;
  };

  struct PinholeCamera : public ICamera
  {
    float             fov;        // field of view (in degrees) 
    Transform         transform;  // (world space)

  private:
    ProjectionMatrix  proj;

  public:
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Point3f& raster_coord, RandomGenerator& gen) override;
    virtual void update(const Film&) override;
  };


}	// namespace ink

