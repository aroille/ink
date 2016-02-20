#pragma once

#include "core/ink.h"
#include "math/point.h"
#include "math/vector.h"
#include "math/normal.h"

namespace ink
{
  struct Ray
  {
    Point3f o;      // origin
    Vec3f   d;      // direction
    uint32  depth;
  };

  struct Instance;

  struct RayHit
  {
    Point3f         p;            // position
    Normal3f        n;            // surface normal
    float           distance_sq;  // squared distance from ray origin
    const Instance* instance;

    void reset()
    {
      p = Point3f(0, 0, 0);
      n = Normal3f(0, 0, 0);
      distance_sq = FLT_MAX;
      instance = nullptr;
    }
  };

} // namespace ink
