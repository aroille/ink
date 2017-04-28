#include "core/renderer.h"
#include "core/filter.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "math/ray.h"

#include <omp.h>

namespace ink
{ 
  SimpleRenderer::SimpleRenderer()
    : filter(new TriangleFilter(0.5, 0.5)) 
    , prim_generator(-0.5, 0.5)
    , diffuse_generator(-1.0, 1.0)
  {
  }

  SimpleRenderer::~SimpleRenderer()
  {
    free(filter);
  }

  void SimpleRenderer::start(Integrator& integrator, Scene& scene, Camera& camera, Film& film)
  {
    this->integrator = &integrator;
    this->scene = &scene;
    this->camera = &camera;
    this->film = &film;

    this->integrator->scene = this->scene;

    // start render
    tile_count_x = (film.width() + tile_size - 1) / tile_size;
    tile_count_y = (film.height() + tile_size - 1) / tile_size;
    tile_count = tile_count_x * tile_count_y;

    next_tile = 0;
    #pragma omp parallel
    {
      thread_task();
    }
  }

  void SimpleRenderer::thread_task()
  {
    while (true)
    {
      uint32 tile_id = next_tile++;
      if (tile_id >= tile_count)
        break;

      // get limits of the tile
      uint32 tile_y = tile_id / tile_count_x;
      uint32 y_min = tile_y * tile_size;
      uint32 y_max = min((tile_y + 1) * tile_size, film->height());

      uint32 tile_x = tile_id % tile_count_x;
      uint32 x_min = tile_x * tile_size;
      uint32 x_max = min((tile_x + 1) * tile_size, film->width());

      for (uint32 y = y_min; y < y_max; ++y)
      {
        for (uint32 x = x_min; x < x_max; ++x)
        {
          Vec3f radiance = Vec3f::zero;
          float weigth = 0.0f;
          for (uint32 s = 0; s < spp; ++s)
          {
            Ray   ray;
            Vec3f raster_coord;
            camera->generate_ray(x, y, ray, raster_coord, prim_generator);

            float w = filter->eval(x - raster_coord.x, y - raster_coord.y);
            radiance += integrator->radiance(ray, diffuse_generator) * w;
            weigth += w;
          }

          if (weigth > 0)
            film->accumulate(x, y, radiance / weigth);
          else
            film->accumulate(x, y, Vec3f::zero);
        }
      }
    }
  }

  Vec3f SimpleIntegrator::radiance(const Ray& ray, RandomGenerator&) const
  {
    int thread_id = omp_get_thread_num();
    return Vec3f((float)thread_id/7.f, 0, 0);

    RayHit hit;
    if (intersect(*scene, ray, hit))
    {
      return Vec3f(1, 0, 0);
    }
    else
    {
      return Vec3f(0, 0, 0);
      //float t = 0.5f * (ray.d.y + 1.0f);
      //return (1 - t) * Vec3f::one + t * Vec3f(0.5, 0.7, 1.0);
    }
  }

  /*
  Vec3f Renderer::integrator(const Ray& ray, RandomGenerator&, int remaining_bounce) const
  {
    RayHit hit;
    if (remaining_bounce && scene_rt.intersect(ray, hit))
      return (Vec3f(0*hit.n.x, 0*hit.n.y, 1*hit.n.z) + Vec3f(0, 0, 1)) * 0.5;
    else
      return Vec3f::zero;
  }
  */
  
  /*
  Vec3f SimpleIntegrator::radiance(const Ray& ray, RandomGenerator& gen, int remaining_bounce, bool primary) const
  {
    if (remaining_bounce == 0)
      return Vec3f::zero;

    RayHit hit;
    if (scene_rt.intersect(ray, hit))
    {
      Ray new_ray;
      Vec3f attenuation;

      Material* material = scene.materials[scene.instances[hit.instance_id].material_id].get();
      material->scatter(ray, hit, new_ray, attenuation, gen);

      return integrator(new_ray, gen, remaining_bounce - 1, false) * attenuation + material->emission;
    }
    else
    {
      return settings.background_color;
    }
  }
  */


}	// namespace ink

