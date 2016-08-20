#include "core/renderer.h"
#include "core/inkrenderer.h"
#include "core/filter.h"
#include "core/material.h"
#include "core/shape.h"
#include "core/log.h"

namespace ink
{ 
  Renderer::Renderer(const Scene& scene, Film& film)
    : scene(scene)
    , film(film)
    , filter(nullptr) 
    , prim_generator(-0.5, 0.5)
    , diffuse_generator(-1.0, 1.0)
  {
  
  }

  void Renderer::prepare(const RenderSettings& s)
  {
    // copy settings
    settings = s;

    // create reconstruction filter
    if (!filter)
      filter = new TriangleFilter(0.5, 0.5);

    // construct ray traversal acceleration structure
    scene_rt.prepare(&scene);
  }

  void Renderer::render(const PinholeCamera& cam)
  {
    // copy camera
    camera = cam;

    // start render threads
    RenderThread::start();

    // wait for completion
    RenderThread::wait();
  }

  void Renderer::renderTask(uint32 thread_id)
  {
    if (thread_id >= settings.threads)
      return;

    // generate 'spp' rays per pixel + compute and filter the radiance allow these rays
    for (uint32 y = thread_id; y < film.height(); y += settings.threads)
    {
      for (uint32 x = 0; x < film.width(); x++)
      {
        Vec3f radiance = Vec3f::zero;
        float weigth = 0.0f;
        for (uint32 s = 0; s < settings.spp; s++)
        {
          Ray     ray;
          Point3f raster_coord;
          camera.generate_ray(x, y, ray, raster_coord, prim_generator);

          float w = filter->eval(x - raster_coord.x, y - raster_coord.y);
          radiance += integrator(ray, diffuse_generator, settings.max_bounce, true) * w;
          weigth += w;
        }

        if (weigth>0)
          film.pixel(x, y) = radiance / weigth;
        else
          film.pixel(x, y) = Vec3f::zero;
      }
    }
  }

  /*
  Vec3f Renderer::integrator(const Ray& ray, RandomGenerator&, int) const
  {
    RayHit hit;
    if (scene_rt.intersect(ray, hit))
    {
      return Vec3f(1,0,0);
    }
    else
    {
      float t = 0.5f * (ray.d.y + 1.0f);
      return (1 - t) * Vec3f::one + t * Vec3f(0.5, 0.7, 1.0);
    }


  }
  */

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
  
  Vec3f Renderer::integrator(const Ray& ray, RandomGenerator& gen, int remaining_bounce, bool primary) const
  {
    RayHit hit;
    uint32 visibility = primary ? VIS_PRIMARY : 0;

    if (remaining_bounce == 0)
      return Vec3f::zero;

    if (scene_rt.intersect(ray, visibility, hit))
    {
      Ray new_ray;
      Vec3f attenuation;

      Material* material = scene.materials[hit.instance->mat_id];
      material->scatter(ray, hit, new_ray, attenuation, gen);

      return integrator(new_ray, gen, remaining_bounce - 1, false) * attenuation + material->emission;
    }
    else
    {
      return settings.background_color;
    }
  }
}	// namespace ink

