
#include "core/camera.h"
#include "math/random.h"

namespace ink
{
  Camera::Camera()
    : fov(60.0f)
    , film_width(640)
    , film_height(480)
  {
    screen_window[0] = -1;
    screen_window[1] =  1;
    screen_window[2] = -1;
    screen_window[3] =  1;

    update_transforms();

    // random generator and distribution
    //random_engine = std::default_random_engine(1729);
    //distr = std::uniform_real_distribution<float>(-0.5, 0.5);
  }

  void Camera::generate_ray(uint32 x, uint32 y, Ray& ray, RandomGenerator& gen)
  {
    Point3f raster_coord;
    raster_coord.x = x + gen();
    raster_coord.y = y + gen();
    raster_coord.z = 0.0;

    Ray r;
    r.o = Point3f(0, 0, 0);
    r.d = Vec3f(raster_to_camera(raster_coord));
    r.depth = 0;
    r.time = 0.0;

    ray = camera_to_world(r);
    ray.d = normalize(ray.d);
  }

  void Camera::update_transforms()
  {
    camera_to_world = transform;
    world_to_camera = inverse(camera_to_world);

    float n = 1;  // near z plane
    float f = 10; // far z plane
    float s = 1.0 / tanf(0.5 * radians(fov));
    float ratio = (float)film_width / (float)film_height;

    Matrix4x4 persp_proj = Matrix4x4( s / ratio,  0,            0,              0,
                                      0,          s,            0,              0,
                                      0,          0,  f / (f - n), -f*n / (f - n),
                                      0,          0,            1,              0);
    camera_to_screen = Transform(persp_proj);

    screen_to_camera = inverse(camera_to_screen);

    screen_to_raster = scale(film_width, film_height, 1) *
                        scale(1.0 / (screen_window[1] - screen_window[0]),
                        1.0 / (screen_window[2] - screen_window[3]), 1) *
                        translate(-screen_window[0], -screen_window[3], 0);

    raster_to_screen = inverse(screen_to_raster);

    raster_to_camera = screen_to_camera * raster_to_screen;
  }

} // namespace ink