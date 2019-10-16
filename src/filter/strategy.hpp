#ifndef PROTOSHOP_FILTER_STRATEGY
#define PROTOSHOP_FILTER_STRATEGY

#include "../image/image.hpp"
#include "kernel.hpp"

class FilterStrategy {
public:
  FilterStrategy() {};
  virtual void apply(Image* target) = 0;
};

class FilterConvolutionStrategy : public FilterStrategy {
private:
  Kernel kernel;
public:
  FilterConvolutionStrategy(Kernel kernel);
  void apply(Image* target);
};

class FilterMedianStrategy : public FilterStrategy {
private:
  int size;
public:
  FilterMedianStrategy(int size);
  void apply(Image* target);
};

#endif
