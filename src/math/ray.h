#pragma once

#include "core/ink.h"
#include "math/point.h"
#include "math/vector.h"

namespace ink
{
  struct Ray
  {
    Point3f o;			// origin
    Vec3f		d;			// direction
    float		time;
    uint32	depth;
  };

  struct Instance;

  struct RayHit
  {
    Point3f					p;						// position
    //Normal3f			n;						// surface normal
    float						distance_sq;	// squared distance from ray origin
    const Instance* instance;
  };

} // namespace ink
