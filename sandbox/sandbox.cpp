
#include "core/renderer.h"
#include "core/camera.h"
#include "math/geometry.h"

using namespace ink;

int main(int, char**)
{
  // Create renderer
  Renderer ink;

  // Setup film and camera
  ink.film.resize(1024, 768);
  ink.camera.fov = 30.0;
  ink.camera.transform = look_at(Point3f(50, 52, 295.6), Point3f(50, 52, 295.6) + Point3f(0, -0.042612, -1), Vec3f(0, 1, 0));

  // Setup scene (see smallpt)
  Sphere sphere_wall(1e5);
  ink.add_instance(&sphere_wall, translate(1e5 + 1, 40.8, 81.6), Vec3f(.75, .25, .25));		// right
  ink.add_instance(&sphere_wall, translate(-1e5 + 99, 40.8, 81.6), Vec3f(.25, .25, .45)); // left
  ink.add_instance(&sphere_wall, translate(50, 40.8, 1e5), Vec3f(.75, .75, .75));					// back
  ink.add_instance(&sphere_wall, translate(50, 40.8, -1e5 + 300), Vec3f(0, 0, 0));				// front
  ink.add_instance(&sphere_wall, translate(50, 1e5, 81.6), Vec3f(.65, .65, .65));					// bottom
  ink.add_instance(&sphere_wall, translate(50, -1e5 + 81.6, 81.6), Vec3f(.65, .65, .65)); // top

  Sphere sphere_light(600);
  ink.add_instance(&sphere_light, translate(50, 681.6 - .27, 81.6), Vec3f(1, 1, 1)); // light

  Sphere sphere(16.5);
  ink.add_instance(&sphere, translate(73, 16.5, 47+10), Vec3f(0.0, 0.0, 0.0)); // mirror
  ink.add_instance(&sphere, translate(27, 16.5, 78), Vec3f(0.5, 0.5, 0.5)); // glass

  // Render and save result
  uint32 spp = 1; // sample per pixel
  ink.render(spp);
  ink.film.save("test.ppm");

  return 0;
}