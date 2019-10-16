#ifndef PROTOSHOP_FILTER_STRATEGY_MEDIAN
#define PROTOSHOP_FILTER_STRATEGY_MEDIAN

#include "../../image/image.hpp"
#include "base.hpp"

class FilterMedianStrategy : public FilterStrategyBase {
private:
  int size;
public:
  FilterMedianStrategy(int size);
  void apply(Image* target);
};

#endif
