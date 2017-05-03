#include "core/scene.h"
#include "core/shape.h"

namespace ink
{ 

  static bool intersect_instance(const Scene& scene, uint32 instance_id, const Ray& ray, RayHit& hit)
  {
    hit.instance_id = instance_id;

    const Instance& i = scene.instances[instance_id];
    const Shape& shape = *(scene.shapes[i.shape_id]);
    const Ray ray_obj = transform_ray(i.world_to_object, ray);

    return shape.intersect(ray_obj, hit);
  }

  bool intersect(const Scene& scene, const Ray& ray, RayHit& hit)
  {
    reset(hit);

    for (uint32 i = 0; i < scene.instances.size(); ++i)
    {
      RayHit inst_hit;
      if (intersect_instance(scene, i, ray, inst_hit) && (inst_hit.t < hit.t))
        hit = inst_hit;
    }

    return (hit.instance_id != UINT32_MAX);
  }

}	// namespace ink

