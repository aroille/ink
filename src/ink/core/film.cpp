#include "core/film.h"
#include "core/log.h"

namespace ink
{
  Film::~Film()
  {
    free(data);
  }

  Film::Film(uint32 width, uint32 height)
    : w(width), h(height)
  {
    data = (Vec3f*)malloc(w*h*sizeof(Vec3f));
  }

  void Film::accumulate(uint32 x, uint32 y, Vec3f value)
  {
    *(data + x + y*w) = value;
  }

  void Film::clear()
  {
    memset(data, 0, w*h*sizeof(Vec3f));
  }
\


  static int to_int(float x)
  {
    return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
    //return int(clamp(x) * 255 + .5);
  }

  bool saveImage(const Film& film, const char* filepath)
  {
    FILE *f = fopen(filepath, "w"); // Write image to PPM file. 
    if (!f)
    {
      INK_LOG_ERROR("Can't open file: " << filepath);
      return false;
    }

    uint32 w = film.width();
    uint32 h = film.height();
    const Vec3f* data = film.data_ptr();

    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);

    for (uint32 i = 0, pixel_count = w*h; i < pixel_count; ++i)
      fprintf(f, "%d %d %d ", to_int(data[i].x), to_int(data[i].y), to_int(data[i].z));

    fclose(f);

    INK_LOG_INFO("Result saved: " << filepath);
    return true;
  }


} // namespace ink