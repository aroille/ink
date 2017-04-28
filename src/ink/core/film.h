#pragma once

#include "math/common.h"
#include "math/vector.h"

namespace ink
{
  class Film
  {
  public:
    Film(uint32 width, uint32 height);
    ~Film();

    inline uint32 width() const  { return w; }
    inline uint32 height() const { return h; }

    void           clear();
    const Vec3f*   data_ptr() const { return data; }

    void           accumulate(uint32 x, uint32 y, Vec3f value);

  private:
    Vec3f* data;
    uint32 w;
    uint32 h;
  };

  bool saveImage(const Film& film, const char* filepath);

}	// namespace ink

