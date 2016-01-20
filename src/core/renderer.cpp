#include "core/renderer.h"
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

  void Renderer::render(uint32 spp)
  {
    camera.film_width = film.width();
    camera.film_height = film.height();
    camera.update_transforms();

    film.clear();

    RandomGenerator generator(-0.5, 0.5);

    // debug
   // uint32 x = 512;
    //uint32 y = 700;

    for (uint32 y = 0; y < film.height(); y++)
    {
      for (uint32 x = 0; x < film.width(); x++)
      {
        Vec3f radiance = Vec3f::zero;

        for (uint32 s = 0; s < spp; s++)
        {
          Ray primary_ray;
          camera.generate_ray(x, y, primary_ray, generator);

          RayHit primary_hit{ Point3f(0, 0, 0), Normal3f(0, 0, 0), FLT_MAX, nullptr };

          for (uint32 i = 0; i < instances.size(); i++)
            //uint32 i = 3;
          {
            RayHit hit;
            Instance& instance = instances[i];
            if (instance.intersect(primary_ray, hit))
            {
              if (hit.distance_sq < primary_hit.distance_sq)
                primary_hit = hit;
            }
          }

          if (primary_hit.instance)
          {
            radiance += primary_hit.instance->color * dot(-primary_ray.d, primary_hit.n);
            //radiance += 0.5f*(Vec3f(primary_hit.n) + Vec3f::one);
            //radiance += Vec3f(primary_hit.n);

          }
        }

        film.pixel(x, y) = radiance / ((float)spp);
        
      }
    }
  }

}	// namespace ink

