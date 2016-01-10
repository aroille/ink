#pragma once

#include "core/ink.h"
#include "math/geometry.h"

namespace ink
{
  class INK_API Camera
  {
  public:
    Camera();

    void set_transform(const Transform&);
    void set_fov(float);
    void set_screen_size(uint32 width, uint32 height);

    void generate_ray(uint32 x, uint32 y, Ray& ray);

  private:
    void update();

  public:
    Transform world_to_camera;
    Transform camera_to_world;

    Transform	camera_to_screen; // projection
    Transform screen_to_camera;

    Transform screen_to_raster;
    Transform raster_to_screen;

    Transform raster_to_camera;

    float fov;
    uint32 screen_width;
    uint32 screen_height;
    float  screen_window[4];
  };

}	// namespace ink

