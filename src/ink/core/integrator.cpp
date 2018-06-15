#include "core/integrator.h"
#include "core/scene.h"
#include "core/material.h"
#include "math/ray.h"

namespace ink
{ 
  Vec3f SimpleIntegrator::trace(const Ray& ray, RandomGenerator& gen, RenderStats& stats) const
  {
    return trace(ray, gen, max_bounce, stats);
  }

  Vec3f SimpleIntegrator::trace(const Ray& ray, RandomGenerator& gen, int remaining_bounce, RenderStats& stats) const
  {
    stats.rayCount++;

    RayHit hit;
    if (intersect(*scene, ray, hit))
    {
      const Instance& instance = scene->instances[hit.instance_id];
      const Material* material = scene->materials[instance.material_id].get();

      // post intersect
      hit.n = normalize(transform_vec(scene->instances[hit.instance_id].object_to_world, hit.n));

      Ray new_ray;
      Vec3f attenuation;

      material->scatter(ray, hit, new_ray, attenuation, gen);
      new_ray.tmin = hit.epsilon;
      new_ray.tmax = FLT_MAX;

      Vec3f next_bounce_radiance = Vec3f::zero;
      if ((remaining_bounce > 0) && (attenuation.length_squared() != 0.f))
        next_bounce_radiance = trace(new_ray, gen, remaining_bounce - 1, stats);

      return next_bounce_radiance * attenuation + material->emission;
    }
    else
    {
      return sky_radiance;
    }
  }

  Vec3f DebugIntegrator::trace(const Ray& ray, RandomGenerator& /*gen*/, RenderStats& stats) const
  {
    stats.rayCount++;

    // Display thread Id
    //int thread_id = omp_get_thread_num();
    //return Vec3f((float)thread_id/7.f, 0, 0);

    RayHit hit;
    if (intersect(*scene, ray, hit))
    {
      // display instanceId of the primary hit
      //return Vec3f((float)(hit.instance_id+1)/scene->instances.size(), 0, 0);

      // display unormalized normal of the primary hit in object space
      return hit.n;
    }
    else
      return Vec3f(0.0, 0.0, 0.5);
  }

}	// namespace ink

