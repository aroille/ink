
#include "core/scene.h"
#include "core/camera.h"
#include "core/shape.h"
#include "core/material.h"

#include "helper_shape.h"

using namespace ink;

void create_cornell_box_scene(Scene& scene, PinholeCamera& camera)
{
  // camera
  camera.fov = 50.f;
  camera.transform = translate(0.f, 0.f, 5.f + 5.f / tan(0.5f * radians(camera.fov)));
  
  // shapes
  SceneShape<TriangleMesh> quad(scene);
  helper::create_quad(quad);

  SceneShape<Sphere> sphere(scene);
  sphere->radius = 1.f;

  // materials
  SceneMaterial<Lambertian> red_lambert(scene);
  red_lambert->albedo = Vec3f(0.75f, 0.25f, 0.25f);

  SceneMaterial<Lambertian> green_lambert(scene);
  green_lambert->albedo = Vec3f(0.25f, 0.75f, 0.25f);

  SceneMaterial<Lambertian> white_lambert(scene);
  white_lambert->albedo = Vec3f(0.75f, 0.75f, 0.75f);

  SceneMaterial<Lambertian> emissive(scene);
  emissive->albedo = Vec3f(0.f, 0.f, 0.f);
  emissive->emission = Vec3f::one * 10.f;

  SceneMaterial<Metal> metal(scene);
  metal->albedo = Vec3f(0.9f, 0.9f, 0.9f);
  metal->roughness = 0.0f;
 
  SceneMaterial<Dielectric> dielectric(scene);
  dielectric->ri = 1.3f;

  // instances
  new_instance(scene, quad, white_lambert, translate(0.0f, 0.0f, -5.f) * scale(10.f));
  new_instance(scene, quad, red_lambert,   translate( -5.0f, 0.0f, 0.f) * rotate_y(90.f) * scale(10.f));
  new_instance(scene, quad, green_lambert, translate(5.0f, 0.0f, 0.f) * rotate_y(-90.f) * scale(10.f));
  new_instance(scene, quad, white_lambert, translate(0.0f, 5.0f, 0.f) * rotate_x(90.f) * scale(10.f));
  new_instance(scene, quad, white_lambert, translate(0.0f, -5.0f, 0.f) * rotate_x(-90.f) * scale(10.f));
  new_instance(scene, sphere, metal, translate(4.5, 4.5, -4.5) * scale(2.f));
  new_instance(scene, sphere, white_lambert, translate(-2.f, -3.f, -2.f) * scale(2.f));
  new_instance(scene, sphere, dielectric, translate(-2.f, 0.f, 2.f) * scale(2.f));
  new_instance(scene, quad, emissive, translate(0.0f, 4.9999f, 0.f) * rotate_x(90.f) * scale(4.f));
}

void create_aras_scene(Scene& scene, PinholeCamera& camera)
{
  camera.fov = 60.0f;
  camera.transform = camera_look_at({ 0, 2, 3 }, { 0, 0, 0 }, { 0, 1, 0 });

  SceneShape<Sphere> sphere(scene);
  sphere->radius = 1.f;

  SceneMaterial<Lambertian> mat0(scene);
  mat0->albedo = Vec3f(0.8f, 0.8f, 0.8f);
  SceneMaterial<Lambertian> mat1(scene);
  mat1->albedo = Vec3f(0.8f, 0.4f, 0.4f);
  SceneMaterial<Lambertian> mat2(scene);
  mat2->albedo = Vec3f(0.4f, 0.8f, 0.4f);

  SceneMaterial<Metal> mat3(scene);
  mat3->albedo = Vec3f(0.4f, 0.4f, 0.8f);
  mat3->roughness = 0.0f;
  SceneMaterial<Metal> mat4(scene);
  mat4->albedo = Vec3f(0.4f, 0.8f, 0.4f);
  mat4->roughness = 0.0f;
  SceneMaterial<Metal> mat5(scene);
  mat5->albedo = Vec3f(0.4f, 0.8f, 0.4f);
  mat5->roughness = 0.2f;
  SceneMaterial<Metal> mat6(scene);
  mat6->albedo = Vec3f(0.4f, 0.8f, 0.4f);
  mat6->roughness = 0.6f;

  SceneMaterial<Dielectric> mat7(scene);
  mat7->ri = 1.5f;

  SceneMaterial<Lambertian> mat8(scene);
  mat8->albedo = Vec3f(0.8f, 0.6f, 0.2f);
  mat8->emission = Vec3f(30.0f, 25.0f, 15.0f);

  new_instance(scene, sphere, mat0, translate(0, -100.5, -1) * scale(100));
  new_instance(scene, sphere, mat1, translate(2, 0, -1) * scale(0.5));
  new_instance(scene, sphere, mat2, translate(0, 0, -1) * scale(0.5));
  new_instance(scene, sphere, mat3, translate(-2, 0, -1) * scale(0.5));
  new_instance(scene, sphere, mat4, translate(2, 0, 1) * scale(0.5));
  new_instance(scene, sphere, mat5, translate(0, 0, 1) * scale(0.5));
  new_instance(scene, sphere, mat6, translate(-2, 0, 1) * scale(0.5));
  new_instance(scene, sphere, mat7, translate(0.5f, 1, 0.5f) * scale(0.5));
  new_instance(scene, sphere, mat8, translate(-1.5f, 1.5f, 0.f) * scale(0.3));
}

void create_sphere_and_triangle_scene(Scene& scene, PinholeCamera& camera)
{
  // Camera
  camera.fov = 45.f;
  camera.transform = camera_look_at(
    Vec3f(4.f, 1.f, 8.f),         // origin
    Vec3f(1.f, 1.f, 0.f),         // target
    Vec3f(0.f, 1.f, 0.f));        // up

  // shapes
  SceneShape<Sphere> sphere(scene);
  sphere->radius = 1.f;

  SceneShape<TriangleMesh> mesh(scene);
  mesh->tri_count = 1;
  mesh->vertices.reset(new Vec3f[3]);
  mesh->indices.reset(new uint32[3]);
  mesh->vertices[0] = Vec3f(-1.0f, 1.f, 0.f);
  mesh->vertices[1] = Vec3f(3.0f, 1.f, -1.f);
  mesh->vertices[2] = Vec3f(1.f, 3.f, 0.f);
  mesh->indices[0] = 0;
  mesh->indices[1] = 1;
  mesh->indices[2] = 2;

  // materials
  SceneMaterial<Lambertian> lambert(scene);
  lambert->albedo = Vec3f(0.75, 0.25, 0.25);
  lambert->emission = Vec3f::zero;

  SceneMaterial<Lambertian> emissive(scene);
  emissive->albedo = Vec3f::zero;
  emissive->emission = Vec3f::one * 5;

  SceneMaterial<Metal> metal(scene);
  metal->albedo = 0.8f * Vec3f::one;
  metal->emission = Vec3f::zero;
  metal->roughness = 0.f;

  // instances
  new_instance(scene, sphere, lambert, translate(-1.0f, 1.f, 0.f));
  new_instance(scene, sphere, metal, translate(3.0f, 1.f, -1.f));
  new_instance(scene, sphere, emissive, translate(1.f, 3.f, 0.f));
  new_instance(scene, sphere, metal, translate(0.f, -500.f, 0.f) * scale(500.f));
  new_instance(scene, mesh, lambert, translate(0.0f, 0.f, 0.f));
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