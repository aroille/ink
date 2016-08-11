#include "core/renderer.h"
#include "core/filter.h"
#include "math/random.h"
#include "core/material.h"
#include "core/shape.h"
#include "core/log.h"

namespace ink
{ 

  InstanceId InkRenderer::add_instance(ShapeId shape, MaterialId material, const Transform& tf, uint32 visibility)
  {
    Instance inst;
    inst.object_to_world = tf;
    inst.world_to_object = inverse(tf);
    inst.shape_id = shape;
    inst.mat_id = material;
    inst.vis = visibility;

    scene.instances.push_back(inst);
    return (uint32)(scene.instances.size() - 1);
  }

  ShapeId InkRenderer::add_shape(Shape* shape)
  {
    scene.shapes.push_back(shape);
    return (uint32)(scene.shapes.size() - 1);
  }

  MaterialId InkRenderer::add_material(Material* material)
  {
    scene.materials.push_back(material);
    return (uint32)(scene.materials.size() - 1);
  }

  void InkRenderer::render(PinholeCamera camera, const RenderSettings& settings)
  {
    // reset film
    film.resize(settings.res_x, settings.res_y);
    film.clear();
    
    // update camera
    camera.update(film);
   
    // build scene acceleration structure
    INK_LOG_INFO("Preparing renderer");
    renderer.prepare();
    INK_LOG_INFO("Start render");
    renderer.render(camera, settings);
    INK_LOG_INFO("Render complete");
  }

  void Renderer::prepare()
  {
    scene_rt.prepare(&scene);
  }

  void Renderer::render(PinholeCamera camera, const RenderSettings& settings)
  {
    background_color = settings.background_color;

    // create random generator
    RandomGenerator generator(-0.5, 0.5);
    RandomGenerator diffuse_generator(-1.0, 1.0);

    // create reconstruction filter
    TriangleFilter filter(0.5, 0.5);

    // generate 'spp' rays per pixel + compute and filter the radiance allow these rays
    for (uint32 y = 0; y < film.height(); y++)
    {
      for (uint32 x = 0; x < film.width(); x++)
      {
        Vec3f radiance = Vec3f::zero;
        float weigth = 0.0f;
        for (uint32 s = 0; s < settings.spp; s++)
        {
          Ray     ray;
          Point3f raster_coord;
          camera.generate_ray(x, y, ray, raster_coord, generator);

          float w = filter.eval(x - raster_coord.x, y - raster_coord.y);
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
    if (remaining_bounce && scene_rt.intersect(ray, visibility, hit))
    {
      Ray new_ray;
      Vec3f attenuation;

      Material* material = scene.materials[hit.instance->mat_id];
      material->scatter(ray, hit, new_ray, attenuation, gen);

      return integrator(new_ray, gen, remaining_bounce - 1, false) * attenuation + material->emission;
    }
    else if (remaining_bounce>0)
    {
      return background_color;
    }
    else
    {
      return Vec3f::zero;
    }
  }
}	// namespace ink

