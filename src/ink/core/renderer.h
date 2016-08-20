#pragma once

#include "core/ink.h"
#include "core/camera.h"
#include "core/film.h"
#include "core/scene.h"
#include "core/settings.h"
#include "math/transform.h"
#include "math/random.h"

#include <vector>
#include <thread>
#include <condition_variable>

namespace ink
{
  struct Shape;
  class Material;
  class Filter;

  class Renderer
  {
  public:
    Renderer(const Scene& scene, Film& film);
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) { return *this;  }

    void          prepare(const RenderSettings& settings);
    void          render(const PinholeCamera& camera);
    void          renderTask(uint32 thread_id);

  private:
    Vec3f         integrator(const Ray& ray, RandomGenerator& gen, int remaining_bounce, bool primary = true) const;

    const Scene&            scene;
    SceneRT                 scene_rt;

    Film&                   film;
    PinholeCamera           camera;
    Filter*                 filter;

    // rnd
    RandomGenerator         prim_generator;
    RandomGenerator         diffuse_generator;

    // settings
    RenderSettings          settings;
  };

}    // namespace ink

