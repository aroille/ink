#include "core/renderer.h"
#include "core/integrator.h"
#include "core/filter.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/material.h"
#include "math/ray.h"

#include <omp.h>

namespace ink
{ 
  void SimpleRenderer::start(Integrator& integrator, Scene& scene, Camera& camera, Film& film, Filter& filter)
  {
    this->integrator = &integrator;
    this->scene = &scene;
    this->camera = &camera;
    this->film = &film;
    this->filter = &filter;

    this->integrator->scene = this->scene;
    this->camera->update(film.width(), film.height());

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
    RandomGenerator prim_generator(-0.5, 0.5);
    RandomGenerator diffuse_generator(-1.0, 1.0);

    for (;;)
    {
      uint32 tile_id = next_tile++;
      if (tile_id >= tile_count)
        break;

      prim_generator.seed(tile_id * random_seed);
      diffuse_generator.seed(tile_id * random_seed);

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
          float pixel_center_x = x + 0.5f;
          float pixel_center_y = y + 0.5f;

          Vec3f radiance = Vec3f::zero;
          float weigth = 0.0f;
          for (uint32 s = 0; s < spp; ++s)
          {
            Ray   ray;
            Vec3f raster_coord;
            camera->generate_ray(x, y, ray, raster_coord, prim_generator);

            float w = filter->eval(pixel_center_x - raster_coord.x, pixel_center_y - raster_coord.y);
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

}	// namespace ink

