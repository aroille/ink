#pragma once

#include "core/ink.h"
#include "core/camera.h"
#include "core/film.h"
#include "core/scene.h"
#include "math/transform.h"

#include <vector>

namespace ink
{
  struct Shape;
  class Material;

  struct RenderSettings
  {
    uint32  res_x;
    uint32  res_y;
    uint32  spp;
    uint32  max_bounce;
    Vec3f   background_color;
  };

  class Renderer
  {
  public:
    Renderer(const Scene& scene, Film& film) : scene(scene), film(film) {}
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) { return *this;  }

    void          prepare();
    void          render(PinholeCamera camera, const RenderSettings& settings);

  private:
    Vec3f         integrator(const Ray& ray, RandomGenerator& gen, int remaining_bounce, bool primary = true) const;

    const Scene&  scene;
    SceneRT       scene_rt;

    Film&         film;
    PinholeCamera camera;

    // settings
    Vec3f         background_color;
  };

  class InkRenderer
  {
  public:
    InkRenderer() : renderer(Renderer(scene, film)) {}
    InkRenderer(const InkRenderer&) = delete;

    void        render(PinholeCamera camera, const RenderSettings& settings);

    InstanceId  add_instance(ShapeId shape, MaterialId material, const Transform& tf, uint32 visibility = VIS_ALL);
    ShapeId     add_shape(Shape*);
    MaterialId  add_material(Material*);

    Film        film;

  private:
    Scene       scene;
    Renderer    renderer;
  };

}    // namespace ink

