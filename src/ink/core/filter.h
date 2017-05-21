#pragma once

namespace ink
{
  class Filter
  {
  public:
    Filter(float extent) : extent(extent){}
    virtual float eval(float relative_x, float relative_y) const = 0;

  public:
    float extent;
  };

  class BoxFilter : public Filter
  {
  public:
    BoxFilter(float width)
      : Filter(width)
      , width(width)
      , half_width(0.5f * width)
    {}

    float eval(float relative_x, float relative_y) const
    { 
      if ((abs(relative_x) >= half_width) || (abs(relative_y) >= half_width))
        return 0.0f;
      return 1.0f;
    }

  private:
    float width;
    float half_width;
  };

  class TriangleFilter : public Filter
  {
  public:
    TriangleFilter(float width)
      : Filter(width)
      , width(width)
      , half_width(0.5f * width)
    {}

    float eval(float relative_x, float relative_y) const
    { 
      return max(0, half_width - abs(relative_x)) * max(0, half_width - abs(relative_y));
    }

  private:
    float width;
    float half_width;
  };

  class GaussianFilter : public Filter
  {
  public:
    GaussianFilter(float width, float alpha) 
      : Filter(width)
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

