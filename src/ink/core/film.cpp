#include "core/film.h"
#include "core/log.h"

namespace ink
{
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
    data = (Vec3f*)malloc(w*h*sizeof(Vec3f));
	clear();
  }

  void Film::accumulate(uint32 x, uint32 y, Vec3f value)
  {
    *(data + x + y*w) += value;
  }

  void Film::clear()
  {
    memset(data, 0, w*h*sizeof(Vec3f));
  }

  int toInt(float x)
  {
    return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
    //return int(clamp(x) * 255 + .5);
  }

  bool Film::save(const char* filepath) const
  {
    FILE *f = fopen(filepath, "w"); // Write image to PPM file. 
    if (!f)
    {    
      INK_LOG("Can't open file: " << filepath);
      return false;
    }

    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);

    for (uint32 i = 0; i < w*h; i++)
      fprintf(f, "%d %d %d ", toInt(data[i].x), toInt(data[i].y), toInt(data[i].z));

    fclose(f);

    INK_LOG("Result saved: " << filepath);
    return true;
  }


} // namespace ink