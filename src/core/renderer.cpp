#include "core/renderer.h"
#include "core/filter.h"
#include "math/random.h"
#include "core/shape.h"
#include "core/log.h"

namespace ink
{ 
  bool intersect(const Instance& instance, const Ray& ray, RayHit& hit)
  {
    RayHit object_hit;
    Ray object_ray = instance.world_to_object(ray);

    if (instance.shape->intersect(object_ray, object_hit))
    {
      hit.p = instance.object_to_world(object_hit.p);
      hit.n = normalize(instance.object_to_world(object_hit.n));
      hit.distance_sq = distance_squared(ray.o, hit.p);
      hit.instance = &instance;
      return true;
    }
    return false;
  }

  bool intersect(const Scene& scene, const Ray& ray, RayHit& hit)
  {
    reset(hit);

    for (uint32 i = 0; i < scene.instances.size(); i++)
    {
      RayHit inst_hit;
      const Instance& instance = scene.instances[i];
      if (intersect(instance, ray, inst_hit))
      {
        if (inst_hit.distance_sq < hit.distance_sq)
          hit = inst_hit;
      }
    }

    return (hit.instance != nullptr);
  }
  void Scene::add(Shape* shape, const Transform& tf, const Vec3f& color)
  {
    Instance inst;
    inst.shape = shape;
    inst.object_to_world = tf;
    inst.world_to_object = inverse(tf);
    inst.color = color;

    instances.push_back(inst);
  }

  void Renderer::render(uint32 spp)
  {
    INK_LOG_INFO("Start render");

    camera.update(film);
    film.clear();

    RandomGenerator generator(-0.5, 0.5);
    TriangleFilter filter(0.5, 0.5);

    // debug
   // uint32 x = 512;
    //uint32 y = 700;

    for (uint32 y = 0; y < film.height(); y++)
    {
      for (uint32 x = 0; x < film.width(); x++)
      {
        Vec3f radiance = Vec3f::zero;
        float weigth = 0.0f;
        for (uint32 s = 0; s < spp; s++)
        { 
          Ray     prim_ray;
          RayHit  prim_hit;
          Point3f raster_coord;

          camera.generate_ray(x, y, prim_ray, raster_coord, generator);
          float w = filter.eval(x - raster_coord.x, y - raster_coord.y);
          
          if (intersect(scene, prim_ray, prim_hit))
          {
            Vec3f prim_radiance = prim_hit.instance->color * dot(-prim_ray.d, prim_hit.n);

            /*
            Ray sec_ray;
            sec_ray.d = prim_ray.d - 2.0f * Vec3f(dot(prim_ray.d, prim_hit.n) * prim_hit.n);
            sec_ray.o = prim_hit.p;
            sec_ray.time = prim_ray.time;
            sec_ray.depth = prim_ray.depth + 1;

            RayHit sec_hit;
            bool has_hit = intersect_world(sec_ray, sec_hit);
            Vec3f sec_radiance = has_hit ? sec_hit.instance->color * dot(-sec_ray.d, sec_hit.n) : Vec3f::zero;
            

            radiance += (prim_radiance + sec_radiance) * 0.5 * w;
            */
            radiance += prim_radiance * w;

            //radiance += 0.5f*(Vec3f(primary_hit.n) + Vec3f::one);
            //radiance += Vec3f(primary_hit.n);
          }
          weigth += w;
        }

        film.pixel(x, y) = radiance / weigth;
        
      }
    }

    INK_LOG_INFO("Render complete");
  }

}	// namespace ink

