#pragma once

#include "core/ink.h"
#include "core/camera.h"
#include "core/film.h"
#include "core/scene.h"
#include "core/settings.h"
#include "math/transform.h"

#include <vector>
#include <thread>
#include <condition_variable>
#include <atomic>

namespace ink
{
  struct Shape;
  class Material;

  class InkRenderer;
  class RenderThread
  {
  public:
    RenderThread();
    void operator ()(uint32 thread_id, InkRenderer* renderer);

    static void start();  // start render
    static void wait();   // wait render to finish

  private:
    static std::atomic_int32_t     remainingTask;
    static std::mutex              mutex;
    static std::condition_variable start_cv;
  };

  class Renderer;
  class InkRenderer
  {
    friend RenderThread;

  public:
    InkRenderer();
    InkRenderer(const InkRenderer&) = delete;
    ~InkRenderer();

    void          render(PinholeCamera camera, const RenderSettings& settings);

    InstanceId    add_instance(ShapeId shape, MaterialId material, const Transform& tf, uint32 visibility = VIS_ALL);
    ShapeId       add_shape(Shape*);
    MaterialId    add_material(Material*);

    Film          film;

  private:
    typedef std::vector<std::thread*> ThreadPool;

    Scene      scene;
    Renderer*  renderer;
    ThreadPool threads;
  };

}    // namespace ink

