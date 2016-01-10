
#include "core/camera.h"

namespace ink
{
  Camera::Camera()
    : fov(60.0f)
    , screen_width(640)
    , screen_height(480)
  {
    screen_window[0] = -1;
    screen_window[1] =  1;
    screen_window[2] = -1;
    screen_window[3] =  1;

    update();
  }

  void Camera::set_transform(const Transform& transform)
  {
    world_to_camera = inverse(transform);
  }

  void Camera::set_fov(float value)
  {
    fov = value;
    update();
  }

  void Camera::set_screen_size(uint32 width, uint32 height)
  {
    screen_width = width;
    screen_height = height;
    update();
  }

  void Camera::generate_ray(uint32 x, uint32 y, Ray& ray)
  {
    Ray r;
    r.o = Point3f(0, 0, 0);
    r.d = Vec3f(raster_to_camera(Point3f(x, y, 0)));
    r.depth = 0;
    r.time = 0.0;

    ray = camera_to_world(r);
    ray.d = normalize(ray.d);
  }

  void Camera::update()
  {
    camera_to_world = inverse(world_to_camera);

    float n = 1;  // near z plane
    float f = 10; // far z plane
    float s = 1.0 / tanf(0.5 * radians(fov));
    float ratio = (float)screen_width / (float)screen_height;

    Matrix4x4 persp_proj = Matrix4x4( s / ratio,  0,            0,              0,
                                      0,          s,            0,              0,
                                      0,          0,  f / (f - n), -f*n / (f - n),
                                      0,          0,            1,              0);
    camera_to_screen = Transform(persp_proj);

    screen_to_camera = inverse(camera_to_screen);

    screen_to_raster =  scale(screen_width, screen_height, 1) *
                        scale(1.0 / (screen_window[1] - screen_window[0]),
                        1.0 / (screen_window[2] - screen_window[3]), 1) *
                        translate(-screen_window[0], -screen_window[3], 0);

    raster_to_screen = inverse(screen_to_raster);

    raster_to_camera = screen_to_camera * raster_to_screen;
  }

} // namespace ink