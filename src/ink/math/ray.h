#pragma once

#include "math/common.h"
#include "math/vector.h"

namespace ink
{
  struct Ray
  {
    Vec3f o;      // origin
    Vec3f d;      // direction
    float tmin;   // ray start
    float tmax;   // ray end
  };

  struct RayHit
  {
    float  t;            // hit point parametric position
    Vec3f  n;            // hit point surface normal
    uint32 instance_id;  // instance hit
  };

  inline void reset(RayHit& hit)
  {
    hit.t = FLT_MAX;
    hit.n = Vec3f::zero;
    hit.instance_id = UINT32_MAX;
  }

  

} // namespace ink
