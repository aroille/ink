#pragma once

#include <vector>
#include "math/common.h"
#include "math/transform.h"

namespace ink
{
  class Shape;
  class Material;
  class Camera;

  struct Instance
  {
    Matrix4x4 object_to_world;
    Matrix4x4 world_to_object;
    uint32    shape_id;
    uint32    material_id;

    Instance() {};
    Instance(uint32 shape, uint32 material, const Transform& transform)
      : object_to_world(transform.matrix())
      , world_to_object(transform.inverse_matrix())
      , shape_id(shape)
      , material_id(material) {};
  };

  struct Scene
  {
    std::vector<Shape*>    shapes;
    std::vector<Material*> materials;
    std::vector<Instance>  instances;
  };

  bool intersect(const Scene& scene, const Ray& ray, RayHit& hit);

}    // namespace ink

