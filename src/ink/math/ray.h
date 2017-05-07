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
    float t;            // parametric position of the hit point
    float epsilon;      
    Vec3f n;            // geometry normal at the hit point 
                        // - unormalized object space before post_intersection
                        // - normalized world space after post_intersection
    uint32 instance_id; // instance hit
  };

  inline void reset(RayHit& hit)
  {
    hit.t = FLT_MAX;
    hit.instance_id = UINT32_MAX;
  }

  

} // namespace ink
