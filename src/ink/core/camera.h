#pragma once

#include "math/transform.h"

namespace ink
{
  class RandomGenerator;
  struct Ray;

  class Camera
  {
  public:
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Vec3f& raster_coord, RandomGenerator& gen) = 0;
    virtual void update(uint32 film_width, uint32 film_height) = 0;
  };

  struct ProjectionMatrix
  {
    Matrix4x4 world_to_camera;
    Matrix4x4 camera_to_world;

    Matrix4x4	camera_to_screen;
    Matrix4x4 screen_to_camera;

    Matrix4x4 screen_to_raster;
    Matrix4x4 raster_to_screen;

    Matrix4x4 raster_to_camera;
  };

  class PinholeCamera : public Camera
  {
  public:
    float             fov;        // field of view (in degrees) 
    Transform         transform;  // (world space)

  private:
    ProjectionMatrix  proj;

  public:
    virtual void generate_ray(uint32 x, uint32 y, Ray& ray, Vec3f& raster_coord, RandomGenerator& gen) override;
    virtual void update(uint32 film_width, uint32 film_height) override;
  };


}	// namespace ink

