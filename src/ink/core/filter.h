#pragma once

namespace ink
{
  class ReconstructionFilter
  {
  public:
    ReconstructionFilter(float extent) : extent(extent){}
    virtual float eval(float relative_x, float relative_y) const = 0;

  public:
    float extent;
  };

  class BoxFilter : public ReconstructionFilter
  {
  public:
    BoxFilter(float width)
      : ReconstructionFilter(width)
      , half_width(0.5f * width)
    {}

    float eval(float relative_x, float relative_y) const
    { 
      if ((abs(relative_x) >= half_width) || (abs(relative_y) >= half_width))
        return 0.0f;
      return 1.0f;
    }

  private:
    float half_width;
  };

  class TriangleFilter : public ReconstructionFilter
  {
  public:
    TriangleFilter(float width)
      : ReconstructionFilter(width)
      , half_width(0.5f * width)
    {}

    float eval(float relative_x, float relative_y) const
    { 
      return max(0, half_width - abs(relative_x)) * max(0, half_width - abs(relative_y));
    }

  private:
    float half_width;
  };

  class GaussianFilter : public ReconstructionFilter
  {
  public:
    GaussianFilter(float width, float alpha) 
      : ReconstructionFilter(width)
      , alpha(alpha)
      , offset(expf(-alpha * width * width))
    {}

    float eval(float relative_x, float relative_y) const
    {
      return eval_1d(relative_x) * eval_1d(relative_y);
    }

  private:
    float eval_1d(float x) const
    {
      return max(0.0f, expf(-alpha * x * x) - offset);
    }

    float alpha;
    float offset;
  };

}	// namespace ink

