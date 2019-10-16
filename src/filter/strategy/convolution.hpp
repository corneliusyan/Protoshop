#ifndef PROTOSHOP_FILTER_STRATEGY_CONVOLUTION
#define PROTOSHOP_FILTER_STRATEGY_CONVOLUTION

#include "../../image/image.hpp"
#include "../kernel.hpp"
#include "base.hpp"

class FilterConvolutionStrategy : public FilterStrategyBase {
private:
  Kernel kernel;
public:
  FilterConvolutionStrategy(Kernel kernel);
  void apply(Image* target);
};

#endif
