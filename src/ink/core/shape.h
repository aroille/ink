#pragma once

#include <memory>

#include "math/common.h"
#include "math/vector3.h"

namespace ink
{
  struct Ray;
  struct RayHit;

  class Shape
  {
  public:
    virtual bool intersect(const Ray& ray, RayHit& hit) const = 0;
  };

  class Sphere : public Shape
  {
  public:
    float radius = 1.f;

  public:
    virtual bool intersect(const Ray& ray, RayHit& hit) const override;
  };

  class TriangleMesh : public Shape
  {
  public:
    uint32 tri_count = 0;
    std::unique_ptr<Vec3f[]> vertices = nullptr;
    std::unique_ptr<uint32[]> indices = nullptr;

  public:
    virtual bool intersect(const Ray& ray, RayHit& hit) const override;
  };

}	// namespace ink

