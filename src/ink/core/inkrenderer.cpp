#include "core/inkrenderer.h"
#include "core/renderer.h"
#include "core/log.h"

namespace ink
{
  std::atomic_int32_t     RenderThread::remainingTask;
  std::mutex              RenderThread::mutex;
  std::condition_variable RenderThread::start_cv;

  RenderThread::RenderThread() {}

  void RenderThread::operator()(uint32 thread_id, InkRenderer* ink)
  {
    INK_LOG_DEBUG("thread " << thread_id);

    // waiting the start
    {
      std::unique_lock<std::mutex> lock(RenderThread::mutex);
      RenderThread::start_cv.wait(lock);
    }

    ink->renderer->renderTask(thread_id);

    remainingTask.fetch_sub(1);
    RenderThread::start_cv.notify_one();
  }

  void RenderThread::start()
  {
    RenderThread::remainingTask = std::thread::hardware_concurrency();
    RenderThread::start_cv.notify_all();
  }

  void RenderThread::wait()
  {
    std::unique_lock<std::mutex> lock(RenderThread::mutex);
    RenderThread::start_cv.wait(lock, []{ return RenderThread::remainingTask == 0; });
  }

  InkRenderer::InkRenderer() 
  {
    // Init thread pool
    uint32 logical_core_count = std::thread::hardware_concurrency();
    threads.resize(logical_core_count);
    for (uint32 i = 0; i < logical_core_count; i++)
    {
      threads[i] = new std::thread(RenderThread(), i, this);
      threads[i]->detach();
    }

    // Create renderer
    renderer = new Renderer(scene, film);
  }

  InkRenderer::~InkRenderer()
  {
    // Delete thread pool
    for (uint32 i = 0; i < threads.size(); i++)
      delete threads[i];
    threads.clear();
  }

  InstanceId InkRenderer::add_instance(ShapeId shape, MaterialId material, const Transform& tf, uint32 visibility)
  {
    Instance inst;
    inst.object_to_world = tf;
    inst.world_to_object = inverse(tf);
    inst.shape_id = shape;
    inst.mat_id = material;
    inst.vis = visibility;

    scene.instances.push_back(inst);
    return (uint32)(scene.instances.size() - 1);
  }

  ShapeId InkRenderer::add_shape(Shape* shape)
  {
    scene.shapes.push_back(shape);
    return (uint32)(scene.shapes.size() - 1);
  }

  MaterialId InkRenderer::add_material(Material* material)
  {
    scene.materials.push_back(material);
    return (uint32)(scene.materials.size() - 1);
  }

  void InkRenderer::render(PinholeCamera camera, const RenderSettings& user_settings)
  {
    // copy user settings
    RenderSettings settings = user_settings;

    uint32 logical_core_count = std::thread::hardware_concurrency();
    settings.threads = settings.threads > 0 ? settings.threads : logical_core_count;
    if (settings.threads > logical_core_count)
    {
      INK_LOG_WARNING("settings.threads is clamped to " << logical_core_count << "(logical_core_count)");
      settings.threads = logical_core_count;
    }

    // reset film
    film.resize(settings.res_x, settings.res_y);
    film.clear();
    
    // update camera
    camera.update(film);
   
    // render
    INK_LOG_INFO("Preparing renderer");
    renderer->prepare(settings);
    INK_LOG_INFO("Start render");
    renderer->render(camera);
    INK_LOG_INFO("Render complete");
  }

}	// namespace ink

