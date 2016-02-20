#include "core/renderer.h"
#include "core/filter.h"
#include "math/random.h"

namespace ink
{
  bool Instance::intersect(const Ray& ray, RayHit& hit) const
  {
    RayHit object_hit;
    Ray object_ray = world_to_object(ray);

    if (shape->intersect(object_ray, object_hit))
    {
      hit.p = object_to_world(object_hit.p);
      hit.n = normalize(object_to_world(object_hit.n));
      hit.distance_sq = distance_squared(ray.o, hit.p);
      hit.instance = this;
      return true;
    }
    return false;
  }

  Renderer::Renderer()
  {
  }

  Renderer::~Renderer()
  {
  }
  
  void Renderer::add_instance(Shape* shape, const Transform& tf, const Vec3f& color)
  {
    Instance inst;
    inst.shape = shape;
    inst.object_to_world = tf;
    inst.world_to_object = inverse(tf);
    inst.color = color;

    instances.push_back(inst);
  }

  bool Renderer::intersect_world(const Ray& ray, RayHit& hit)
  {
    hit.reset();

    for (uint32 i = 0; i < instances.size(); i++)
    {
      RayHit inst_hit;
      Instance& instance = instances[i];
      if (instance.intersect(ray, inst_hit))
      {
        if (inst_hit.distance_sq < hit.distance_sq)
          hit = inst_hit;
      }
    }

    return (hit.instance != nullptr);
  }

  void Renderer::render(uint32 spp)
  {
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
          
          if (intersect_world(prim_ray, prim_hit))
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
  }

}	// namespace ink

