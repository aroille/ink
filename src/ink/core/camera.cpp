
#include "core/camera.h"
#include "math/random.h"

namespace ink
{
  void PinholeCamera::generate_ray(uint32 x, uint32 y, Ray& ray, Vec3f& raster_coord, RandomGenerator& gen)
  {
    // Random raster position
    raster_coord.x = x + gen();
    raster_coord.y = y + gen();
    raster_coord.z = 0.0;

    // Ray in camera space
    Ray r;
    r.o = Vec3f::zero;
    r.d = transform_point(proj.raster_to_camera, raster_coord);
    r.tmin = 0.f;
    r.tmax = FLT_MAX;

    // Ray in world space
    ray = transform_ray(proj.camera_to_world, r);
  }

  void PinholeCamera::update(uint32 film_width, uint32 film_height)
  {
    const float screen_window[4] = { -1.0, 1.0, -1.0, 1.0 };

    proj.camera_to_world = transform.matrix();
    proj.world_to_camera = transform.inverse_matrix();

    float n = 1.f;  // near z plane
    float f = 10.f; // far z plane
    float s = 1.f / tanf(0.5f * radians(fov));
    float ratio = (float)film_width / (float)film_height;

    proj.camera_to_screen = Matrix4x4(-s / ratio, 0, 0, 0,
                                      0,          -s,            0,              0,
                                      0,          0,  -f / (f - n), -f*n / (f - n),
                                      0,          0,            1,              0);

    proj.screen_to_camera = Matrix4x4::inverse(proj.camera_to_screen);

    Transform screen_to_raster = scale((float)film_width, (float)film_height, 1.f) *
                                 scale(1.f / (screen_window[1] - screen_window[0]),
                                 1.f / (screen_window[2] - screen_window[3]), 1.f) *
                                 translate(-screen_window[0], -screen_window[3], 0.f);

    proj.screen_to_raster = screen_to_raster.matrix();
    proj.raster_to_screen = screen_to_raster.inverse_matrix();

    proj.raster_to_camera = Matrix4x4::mul(proj.screen_to_camera, proj.raster_to_screen);
  }

} // namespace ink