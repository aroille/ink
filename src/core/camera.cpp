
#include "core/camera.h"
#include "math/random.h"
#include "core/film.h"

namespace ink
{
  void PinholeCamera::generate_ray(uint32 x, uint32 y, Ray& ray, Point3f& raster_coord, RandomGenerator& gen)
  {
    raster_coord.x = x + gen();
    raster_coord.y = y + gen();
    raster_coord.z = 0.0;

    Ray r;
    r.o = Point3f(0, 0, 0);
    r.d = Vec3f(proj.raster_to_camera(raster_coord));
    r.depth = 0;

    ray = proj.camera_to_world(r);
    ray.d = normalize(ray.d);
  }

  void PinholeCamera::update(const Film& film)
  {
    const float screen_window[4] = { -1.0, 1.0, -1.0, 1.0 };

    proj.camera_to_world = transform;
    proj.world_to_camera = inverse(proj.camera_to_world);

    float n = 1;  // near z plane
    float f = 10; // far z plane
    float s = 1.0 / tanf(0.5 * radians(fov));
    float ratio = (float)film.width() / (float)film.height();

    Matrix4x4 persp_proj = Matrix4x4( s / ratio,  0,            0,              0,
                                      0,          s,            0,              0,
                                      0,          0,  f / (f - n), -f*n / (f - n),
                                      0,          0,            1,              0);
    proj.camera_to_screen = Transform(persp_proj);

    proj.screen_to_camera = inverse(proj.camera_to_screen);

    proj.screen_to_raster = scale(film.width(), film.height(), 1) *
                        scale(1.0 / (screen_window[1] - screen_window[0]),
                        1.0 / (screen_window[2] - screen_window[3]), 1) *
                        translate(-screen_window[0], -screen_window[3], 0);

    proj.raster_to_screen = inverse(proj.screen_to_raster);

    proj.raster_to_camera = proj.screen_to_camera * proj.raster_to_screen;
  }

} // namespace ink