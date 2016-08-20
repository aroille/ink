#pragma once

#include "core/ink.h"
#include "math/geometry.h"

namespace ink
{
  struct RenderSettings
  {
    uint32  res_x;
    uint32  res_y;
    uint32  spp;
    uint32  max_bounce;
    Vec3f   background_color;
    uint32  threads;
  };
}    // namespace ink

