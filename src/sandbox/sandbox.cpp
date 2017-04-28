
#include "core/renderer.h"
#include "core/scene.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/shape.h"
#include "core/material.h"

using namespace ink;

//void scene_cornell_box(Scene& scene, PinholeCamera& camera);
//void scene_debug(InkRenderer& ink, PinholeCamera& camera);

void create_scene(Scene& scene, PinholeCamera& camera)
{
  // Camera
  camera.fov = 30.f;
  camera.transform = camera_look_at(
    Vec3f(0.f, 1.f, 5.f),         // origin
    Vec3f(0.f, 1.f, 0.f),         // target
    Vec3f(0.f, 1.f, 0.f));        // up

  // shapes
  Sphere* sphere = new Sphere();
  sphere->radius = 1.f;
  scene.shapes.push_back(sphere);

  // instances
  scene.instances.push_back(Instance(0, 0, translate(0.f, 1.f, 0.f)));
}

int main(int, char**)
{
  // scene description
  Scene scene;
  PinholeCamera camera;
  create_scene(scene, camera);

  // integrator setup
  SimpleIntegrator integrator;

  // renderer setup
  SimpleRenderer renderer;
  renderer.spp = 1;
  renderer.tile_size = 16;

  // film
  Film film(512, 512);

  // start render
  renderer.start(integrator, scene, camera, film);
  
  // Save result
  saveImage(film, "test.ppm");
  system("\"C:\\Program Files (x86)\\XnView\\xnview.exe\" test.ppm");
  return 0; 
}

/*
void scene_cornell_box(InkRenderer& ink, PinholeCamera& camera)
{
  // Materials
  LambertMaterial* mat_red = new LambertMaterial(Vec3f(0.75, 0.25, 0.25)); 
  LambertMaterial* mat_green = new LambertMaterial(Vec3f(0.25, 0.75, 0.25));
  LambertMaterial* mat_grey = new LambertMaterial(Vec3f(0.75, 0.75, 0.75));
  MetalMaterial* mat_metal = new MetalMaterial(Vec3f(0.75, 0.75, 0.75), 0.05);
  LambertMaterial* mat_emissive = new LambertMaterial(Vec3f(0.75, 0.75, 0.75));
  mat_emissive->emission = Vec3f(20,20,20);

  MaterialId mat_red_id = ink.add_material(mat_red);
  MaterialId mat_green_id = ink.add_material(mat_green);
  MaterialId mat_grey_id = ink.add_material(mat_grey);
  MaterialId mat_metal_id = ink.add_material(mat_metal);
  MaterialId mat_emissive_id = ink.add_material(mat_emissive);

  // Shapes & instances
  Sphere* wall = new Sphere();
  wall->radius = 1e4;
  ShapeId wall_id = ink.add_shape(wall);

  ink.add_instance(wall_id, mat_grey_id, translate(0, wall->radius + 50, 0));       // top
  ink.add_instance(wall_id, mat_grey_id, translate(0, -wall->radius - 50, 0));	    // bottom
  ink.add_instance(wall_id, mat_red_id, translate(-wall->radius - 50, 0, 0));	      // left
  ink.add_instance(wall_id, mat_green_id, translate(wall->radius + 50, 0, 0));	    // right
  ink.add_instance(wall_id, mat_grey_id, translate(0, 0, -wall->radius));	          // back
  ink.add_instance(wall_id, mat_grey_id, translate(0, 0, wall->radius + 100), 0);		// front

  Sphere* sphere = new Sphere();
  sphere->radius = 24;
  ShapeId sphere_id = ink.add_shape(sphere);

  ink.add_instance(sphere_id, mat_emissive_id, translate(0, 50-sphere->radius*0.5, 20)*scale(0.1, 0.1, 0.1));      // mirror
  ink.add_instance(sphere_id, mat_metal_id, translate(-25, -50 + sphere->radius, 20));      // mirror
  //ink.add_instance(sphere_id, translate(27, 16.5, 78), Vec3f(0.5, 0.5, 0.5));           // glass


  // Camera
  camera.fov = 45.0;
  camera.transform = camera_look_at(
    Point3f(0, 0, 200),
    Point3f(0, 0, 200-1),
    Vec3f(0, 1, 0));
}


void scene_debug(InkRenderer& ink, PinholeCamera& camera)
{
  // Materials
  MetalMaterial*   mat_metal = new MetalMaterial(Vec3f(0.85, 0.85, 0.85), 0.2);
  LambertMaterial* mat_red = new LambertMaterial(Vec3f(0.75, 0.25, 0.25));
  LambertMaterial* mat_green = new LambertMaterial(Vec3f(0.25, 0.75, 0.25));
  LambertMaterial* mat_grey = new LambertMaterial(Vec3f(0.5, 0.5, 0.5));

  MaterialId mat_metal_id = ink.add_material(mat_metal);
  MaterialId mat_red_id = ink.add_material(mat_red);
  MaterialId mat_green_id = ink.add_material(mat_green);
  MaterialId mat_grey_id = ink.add_material(mat_grey);

  // Shapes & instances
  Sphere* small = new Sphere(); small->radius = 0.5;
  ShapeId small_id = ink.add_shape(small);

  ink.add_instance(small_id, mat_metal_id, translate(0, 0.5, 0.0));
  ink.add_instance(small_id, mat_red_id, translate(-1.5, 1, 0.0));
  ink.add_instance(small_id, mat_green_id, translate(1.0, 1, 0.0));

  Sphere* big = new Sphere(); big->radius = 100.;
  ShapeId big_id = ink.add_shape(big);

  ink.add_instance(big_id, mat_grey_id, translate(0, -100, 0.0));

  // Camera
  camera.fov = 30.0;
  camera.transform = camera_look_at(
    Point3f(0, 1.5, 5),         // origin
    Point3f(0, 1, 0),           // target
    Vec3f(0, 1, 0)              // up
    );
}
*/