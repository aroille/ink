#pragma once

#include "core/ink.h"
#include "math/point.h"
#include "math/vector.h"
#include "math/normal.h"

namespace ink
{
  struct Instance;

  struct Ray
  {
    Point3f o;      // origin
    Vec3f   d;      // direction
  };

  struct RayHit
  {
    Point3f         p;            // hit point position
    Normal3f        n;            // hit point surface normal
    float           distance_sq;  // squared distance from ray origin
    const Instance* instance;     // instance hit
  };

  inline void reset(RayHit& hit)
  {
    hit.p = Point3f(0, 0, 0);
    hit.n = Normal3f(0, 0, 0);
    hit.distance_sq = FLT_MAX;
    hit.instance = nullptr;
  }

} // namespace ink
