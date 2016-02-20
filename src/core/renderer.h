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
  };

  struct INK_API Scene
  {
    std::vector<Instance> instances;

    void add(Shape* shape, const Transform& tf, const Vec3f& color);
  };

  struct INK_API Renderer
  {
    PinholeCamera camera;
    Film          film;
    Scene         scene;

    void render(uint32 spp = 1);
  };
}    // namespace ink

