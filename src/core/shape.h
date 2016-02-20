#pragma once

#include "core/ink.h"
#include "math/geometry.h"

namespace ink
{
  struct Shape
  {
    virtual bool intersect(const Ray& ray, RayHit& hit) const = 0;
  };

  struct Sphere : public Shape
  {
    float radius;

    virtual bool intersect(const Ray& ray, RayHit& hit) const override;
  };

}	// namespace ink

