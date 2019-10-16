#ifndef PROTOSHOP_FILTER_STRATEGY_COMPLEX
#define PROTOSHOP_FILTER_STRATEGY_COMPLEX

#include "../../image/image.hpp"
#include "base.hpp"

class FilterUnsharpStrategy : public FilterStrategyBase {
public:
  void apply(Image* target);
};

class FilterHighboostStrategy : public FilterStrategyBase {
private:
  double alpha;
public:
  FilterHighboostStrategy(double alpha);
  void apply(Image* target);
};

#endif
