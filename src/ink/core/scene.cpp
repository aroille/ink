#include "core/scene.h"
#include "core/shape.h"

namespace ink
{ 

  static bool intersect_instance(const Scene& scene, uint32 instance_id, const Ray& ray, RayHit& hit)
  {
    const Instance& i = scene.instances[instance_id];
    const Shape& shape = *(scene.shapes[i.shape_id]);

    const Ray ray_obj = transform_ray(i.world_to_object, i.object_to_world, ray);

    if (shape.intersect(ray_obj, hit))
    {
      hit.n = normalize(transform_vec(i.object_to_world, hit.n));
      hit.instance_id = instance_id;
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
      if (intersect_instance(scene, i, ray, inst_hit))
      {
        if (inst_hit.t < hit.t)
          hit = inst_hit;
      }
    }

    return (hit.instance_id != UINT32_MAX);
  }

}	// namespace ink

