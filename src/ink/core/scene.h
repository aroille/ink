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
    uint32    material_id;;
  };

  struct Scene
  {
    std::vector<Shape*>    shapes;
    std::vector<Material*> materials;
    std::vector<Instance>  instances;
  };

  inline Instance make_instance(uint32 shape_id, uint32 material_id, const Transform& transform)
  {
    return {transform.matrix(), transform.inverse_matrix(), shape_id, material_id};
  }

  bool intersect(const Scene& scene, const Ray& ray, RayHit& hit);

}    // namespace ink

