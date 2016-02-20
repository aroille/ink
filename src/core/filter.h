#pragma once

#include "core/ink.h"

namespace ink
{
  class INK_API Filter
  {
  public:
    Filter(float xw, float yw) : x_width(xw), y_width(yw) {}
    virtual float eval(float x, float y) const = 0;

  protected:
    float x_width;
    float y_width;
  };

  class INK_API BoxFilter : public Filter
  {
  public:
    BoxFilter(float xw, float yw) : Filter(xw, yw) {}

    float eval(float, float) const
    { 
      return 1.0f; 
    }
  };

  class INK_API TriangleFilter : public Filter
  {
  public:
    TriangleFilter(float xw, float yw) : Filter(xw, yw) {}

    float eval(float x, float y) const
    { 
      return max(0, x_width - abs(x)) * max(0, y_width - abs(y));
    }
  };

  class INK_API GaussianFilter : public Filter
  {
  public:
    GaussianFilter(float xw, float yw, float a) 
      : Filter(xw, yw) 
      , alpha(a)
      , exp_x(expf(-a*xw*xw))
      , exp_y(expf(-a*yw*yw))
    {}

    float eval(float x, float y) const
    {
      return eval_1d(x, exp_x) * eval_1d(y, exp_y);
    }

    float eval_1d(float x, float offset) const
    {
      return max(0.0f, expf(-alpha*x*x) - offset);
    }

  private:
    float alpha;
    float exp_x;
    float exp_y;
  };

}	// namespace ink

