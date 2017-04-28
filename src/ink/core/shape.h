#pragma once

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
    float radius;

  public:
    virtual bool intersect(const Ray& ray, RayHit& hit) const override;
  };

}	// namespace ink

