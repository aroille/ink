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
    //float   tmin;
    //float   tmax;
  };

  struct RayHit
  {
    float           t;            // hit point position
    float           epsilon;
    Normal3f        n;            // hit point surface normal
    const Instance* instance;     // instance hit

    inline void reset()
    {
      t = FLT_MAX;
      epsilon = 0;
      n = Normal3f(0, 0, 0);
      instance = nullptr;
    };

  };

  

} // namespace ink
