#pragma once

#include "core/ink.h"
#include "math/geometry.h"

namespace ink
{
	class INK_API Shape
	{
		public:
			Shape() {}
			virtual bool intersect(const Ray& ray, RayHit& hit) const = 0;
	};

	class INK_API Sphere : public Shape
	{
		public:
			Sphere(float radius = 0.5f) : Shape(), radius(radius) {}
			bool intersect(const Ray& ray, RayHit& hit) const;

		private:
			float radius;
	};

}	// namespace ink

