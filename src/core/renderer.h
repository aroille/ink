#pragma once

#include "core/ink.h"
#include "core/camera.h"
#include "core/film.h"
#include "core/shape.h"
#include "math/geometry.h"
#include "math/transform.h"

#include <vector>

namespace ink
{
  template class INK_API std::vector<Instance>;

  struct Instance
  {
    Transform object_to_world;
    Transform world_to_object;
    Shape*    shape;
    Vec3f     color;

    bool intersect(const Ray& ray, RayHit& hit) const;
  };

  class INK_API Renderer
  {
  public:
    Renderer();
    ~Renderer();

    void add_instance(Shape* shape, const Transform& tf, const Vec3f& color);
    void render(uint32 spp = 1);

  public:
    Camera camera;
    Film film;

  private:
    std::vector<Instance> instances;
  };

}    // namespace ink

