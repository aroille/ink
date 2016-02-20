#include "core/film.h"
#include "core/log.h"

namespace ink
{
  Film::Film()
    : data(nullptr), w(0), h(0)
  {}

  Film::~Film()
  {
    free(data);
  }

  Film::Film(uint32 width, uint32 height)
    : data(nullptr), w(0), h(0)
  {
    resize(width, height);
  }

  void Film::resize(uint32 width, uint32 height)
  {
    w = width;
    h = height;

    free(data);
    data = (Pixel*)malloc(w*h*sizeof(Pixel));
  }

  Vec3f& Film::pixel(uint32 x, uint32 y)
  {
    return (data + x + y*w)->xyz;
  }

  void Film::clear()
  {
    memset(data, 0, w*h*sizeof(Pixel));
  }

  int toInt(float x)
  {
    return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
  }

  bool Film::save(const char* filepath) const
  {
    FILE *f = fopen(filepath, "w"); // Write image to PPM file. 
    if (!f)
    {    
      INK_LOG_ERROR("Film", "Can't open file: " << filepath);
      return false;
    }

    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);

    for (uint32 i = 0; i < w*h; i++)
      fprintf(f, "%d %d %d ", toInt(data[i].xyz.x), toInt(data[i].xyz.y), toInt(data[i].xyz.z));

    INK_LOG_INFO("Film", "Result saved: " << filepath);
    return true;
  }


} // namespace ink