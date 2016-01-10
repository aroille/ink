#include "core/renderer.h"

namespace ink
{

	bool Instance::intersect(const Ray& ray, RayHit& hit) const
	{
		RayHit object_hit;
		Ray object_ray = world_to_object(ray);
		
		if (shape->intersect(object_ray, object_hit))
		{
			hit.p = object_to_world(object_hit.p);
			hit.distance_sq = distance_squared(ray.o, hit.p);
			hit.instance = this;
			return true;
		}
		return false;
	}

	Renderer::Renderer()
	{ 
		instances = new std::vector<Instance>(); 
	}

	Renderer::~Renderer()
	{ 
		delete instances; 
	}

	void Renderer::add_instance(Shape* shape, const Transform& tf, const Vec3f& color)
	{
		Instance inst;
		inst.shape = shape;
		inst.object_to_world = tf;
		inst.world_to_object = inverse(tf);
		inst.color = color;

		instances->push_back(inst);
	}

	void Renderer::render()
	{
		film.clear();
		camera.set_screen_size(film.width(), film.height());

		// debug
		//uint32 x = 250;
		//uint32 y = 250;

		for (uint32 y = 0; y < film.height(); y++)
		{
			for (uint32 x = 0; x < film.width(); x++)
			{
				Ray primary_ray;
				camera.generate_ray(x, y, primary_ray);

				RayHit primary_hit{ Point3f(0, 0, 0), FLT_MAX, nullptr };

				for (uint32 i = 0; i < instances->size(); i++)
				{
					RayHit hit;
					Instance& instance = (*instances)[i];		
					if (instance.intersect(primary_ray, hit))
					{
						if (hit.distance_sq < primary_hit.distance_sq)
							primary_hit = hit;
					}
				}

				if (primary_hit.instance)
				{
					Vec3f& r = film.pixel(x, y);
					r = primary_hit.instance->color;
				}
			}
		}
	}

}	// namespace ink

