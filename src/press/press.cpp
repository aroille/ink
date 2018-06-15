
#include "core/renderer.h"
#include "core/integrator.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/filter.h"

#include "scene_samples.h"

using namespace ink;

int main(int, char**)
{
  Scene scene;
  PinholeCamera camera;
  create_cornell_box_scene(scene, camera);

  SimpleIntegrator integrator;
  integrator.max_bounce = 10;
  integrator.sky_radiance = Vec3f(0.7f, 0.7f, 0.7f);

  SimpleRenderer renderer;
  renderer.spp = 128;
  renderer.tile_size = 16;

  Film film(320, 320);
  BoxFilter filter(1.f);

  // start rendering
  renderer.start(integrator, scene, camera, film, filter);

  film.save("test.ppm");
  system("\"C:\\Program Files (x86)\\XnView\\xnview.exe\" test.ppm");

  return 0; 
}
