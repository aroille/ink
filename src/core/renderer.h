#pragma once

#include "core/ink.h"
#include "core/camera.h"
#include "core/film.h"
#include "math/transform.h"

#include <vector>

namespace ink
{
  struct Shape;

  struct Instance
  {
    Transform object_to_world;
    Transform world_to_object;
    Shape*    shape;
    Vec3f     color;
  };

  struct Scene
  {
    std::vector<Instance> instances;

    void add(Shape* shape, const Transform& tf, const Vec3f& color);
  };

  struct Renderer
  {
    PinholeCamera camera;
    Film          film;
    Scene         scene;

    void render(uint32 spp = 1);
  };
}    // namespace ink

