#include "core/renderer.h"
#include "core/filter.h"
#include "math/random.h"
#include "core/shape.h"
#include "core/log.h"

namespace ink
{ 

  bool Instance::intersect(const Scene& scene, const Ray& ray, RayHit& hit) const
  {
    RayHit object_hit;
    Ray object_ray = world_to_object(ray);

    const Shape& shape = *(scene.shapes[shape_id]);

    if(shape.intersect(object_ray, object_hit))
    {
      //Point3f p = ray.o + object_hit.t * ray.d;
      hit.t = object_hit.t;
      hit.epsilon = object_hit.epsilon;
      hit.n = normalize(object_to_world(object_hit.n));
      hit.instance = this;
      return true;
    }
    return false;
  }

  bool SceneRT::intersect(const Ray& ray, uint32 visibility, RayHit& hit) const
  {
    hit.reset();

    for (uint32 i = 0; i < scene->instances.size(); i++)
    {
      const Instance& instance = scene->instances[i];

      if ((instance.vis & visibility) != visibility)
        continue;

      RayHit inst_hit;
      if (instance.intersect(*scene, ray, inst_hit))
      {
        if (inst_hit.t < hit.t)
          hit = inst_hit;
      }
    }

    return (hit.instance != nullptr);
  }

}	// namespace ink

