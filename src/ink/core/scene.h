#pragma once

#include "core/ink.h"
#include "math/transform.h"
#include <vector>

namespace ink
{
  struct Shape;
  class Material;

  typedef uint32 ShapeId;
  typedef uint32 MaterialId;
  typedef uint32 InstanceId;

  struct Scene
  {
    std::vector<Shape*>     shapes;
    std::vector<Material*>  materials;
    std::vector<Instance>   instances;
  };


  // TODO: implement bvh (or use embree)
  class SceneRT
  {
  public:
    void prepare(const Scene* s) { scene = s; }
    bool intersect(const Ray& ray, uint32 visibility, RayHit& hit) const; // TODO: implement bvh (or use embree)

  private:
    const Scene* scene;
  };

  enum Visibility
  {
    VIS_PRIMARY = 1,
    VIS_ALL = VIS_PRIMARY
  };

  struct Instance
  {
    Transform   object_to_world;
    Transform   world_to_object;
    uint32      flags;
    uint32      shape_id;
    uint32      mat_id;
    uint32      vis;

    bool intersect(const Scene& scene, const Ray& ray, RayHit& hit) const;
  };

}    // namespace ink

