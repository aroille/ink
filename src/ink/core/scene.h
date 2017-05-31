#pragma once

#include <vector>
#include "math/common.h"
#include "math/transform.h"

namespace ink
{
  class Shape;
  class Material;

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

  bool intersect(const Scene& scene, const Ray& ray, RayHit& hit);




  struct ShapeId { uint32 id; };
  template <class Type> class SceneShape
  {
  public:
    SceneShape(Scene& scene)
      : ptr(new Type())
      , id({(uint32)scene.shapes.size()})
    {
      scene.shapes.push_back(ptr);
    }

    Type* operator->() { return ptr; }
    operator ShapeId() const { return id; }

  private:
    Type* ptr;
    ShapeId id;
  };

  struct MaterialId { uint32 id; };
  template <class Type> class SceneMaterial
  {
  public:
    SceneMaterial(Scene& scene)
      : ptr(new Type())
      , id({(uint32)scene.materials.size()})
    {
      scene.materials.push_back(ptr);
    }

    Type* operator->() { return ptr; }
    operator MaterialId() const { return id; }

  private:
    Type* ptr;
    MaterialId id;
  };

  inline void new_instance(Scene& scene, ShapeId shape, MaterialId material, const Transform& transform)
  {
    return scene.instances.push_back({transform.matrix(), transform.inverse_matrix(), shape.id, material.id});
  }

  
}    // namespace ink

