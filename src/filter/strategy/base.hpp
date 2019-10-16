#ifndef PROTOSHOP_FILTER_STRATEGY_BASE
#define PROTOSHOP_FILTER_STRATEGY_BASE

#include "../../image/image.hpp"

class FilterStrategyBase {
public:
  FilterStrategyBase() {};
  virtual void apply(Image* target) = 0;
};

#endif
