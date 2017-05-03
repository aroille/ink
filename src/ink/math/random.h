#pragma once

#include <random>

namespace ink
{
  class RandomGenerator
  {
  public:
    RandomGenerator(float min, float max)
    {
      random_engine = new std::mt19937(1729);
      distr = new std::uniform_real_distribution<>(min, max);
    }
    
    ~RandomGenerator()
    {
      delete distr;
      delete random_engine;
    }

    void seed(uint32_t s)
    {
      random_engine->seed(s);
    }

    float operator ()()
    {
      return (*distr)(*random_engine);
    }

  private:
      std::mt19937* random_engine; // this class is not thread-safe !
      std::uniform_real_distribution<>* distr;
  };

}	// namespace ink

