
#include "core/renderer.h"
#include "core/camera.h"
#include "math/geometry.h"

using namespace ink;

int main(int, char**)
{
  // Create renderer
  Renderer ink;

  // Setup film and camera
  ink.film.resize(256, 256);  //(1024, 768);

  ink.camera.fov = 30.0;
  ink.camera.transform = look_at(Point3f(50, 52, 295.6), 
                                 Point3f(50, 52, 295.6) + Point3f(0, -0.042612, -1),
                                 Vec3f(0, 1, 0));

  // Sphere based cornell box, from smallpt (http://www.kevinbeason.com/smallpt/)
  Sphere wall(1e5);
  ink.scene.add(&wall, translate(1e5 + 1, 40.8, 81.6),   Vec3f(.75, .25, .25));	// right
  ink.scene.add(&wall, translate(-1e5 + 99, 40.8, 81.6), Vec3f(.25, .25, .45));  // left
  ink.scene.add(&wall, translate(50, 40.8, 1e5),         Vec3f(.75, .75, .75));	// back
  ink.scene.add(&wall, translate(50, 40.8, -1e5 + 300),  Vec3f(0, 0, 0));			  // front
  ink.scene.add(&wall, translate(50, 1e5, 81.6),         Vec3f(.65, .65, .65));	// bottom
  ink.scene.add(&wall, translate(50, -1e5 + 81.6, 81.6), Vec3f(.65, .65, .65));  // top

  Sphere light(600);
  ink.scene.add(&light, translate(50, 681.6 - .27, 81.6), Vec3f(1, 1, 1));        // light

  Sphere sphere(16.5);
  ink.scene.add(&sphere, translate(73, 16.5, 47 + 10), Vec3f(0.0, 0.0, 0.0));  // mirror
  ink.scene.add(&sphere, translate(27, 16.5, 78), Vec3f(0.5, 0.5, 0.5));  // glass

  // Render and save result
  uint32 spp = 16; // sample per pixel
  ink.render(spp);
  ink.film.save("test.ppm");

  return 0;
}