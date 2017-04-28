#pragma once

#include <float.h>
#include <cstdint>
#include <cmath>
#include <cstring>

// common types
typedef std::int8_t    int8;
typedef std::int16_t   int16;
typedef std::int32_t   int32;
typedef std::int64_t   int64;
typedef std::uint8_t   uint8;
typedef std::uint16_t  uint16;
typedef std::uint32_t	 uint32;
typedef std::uint64_t	 uint64;

namespace ink
{
  // Useful mathematical const
  static const float Pi = 3.1415926535897932f;
  static const float inv_Pi = 0.31830988618f;
  static const float half_Pi = 1.57079632679f;
  static const float delta = 0.00001f; // Magic numbers for numerical precision


  inline float abs(float x)
  {
    return std::fabs(x);
  }

  inline float lerp(float a, float b, float value)
  {
    return a + value*(b - a);
  }

  inline float clamp(float in, float min = 0.0f, float max = 1.0f)
  {
    return (in < min ? min : (in > max ? max : in));
  }

  inline bool near_equal(float a, float b, float delta = ink::delta)
  {
    return (abs(a - b) > delta ? false : true);
  }

  inline float max(float a, float b)
  {
    return a >= b ? a : b;
  }

  inline float min(float a, float b)
  {
    return a <= b ? a : b;
  }

  inline float radians(float deg)
  {
    return Pi * deg / 180.0f;
  }

  inline bool quadratic(float A, float B, float C, float& t0, float& t1)
  {
    float discrim = B*B - 4 * A*C;
    if (discrim <= 0)
      return false;

    float root_discrim = sqrtf(discrim);

    float q;
    if (B < 0)	q = -0.5 * (B - root_discrim);
    else				q = -0.5 * (B + root_discrim);
    t0 = q / A;
    t1 = C / q;

    if (t0 > t1)
    {
      float t = t0;
      t0 = t1;
      t1 = t;
    }
    return true;
  }

} // namespace ink


