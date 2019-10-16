#ifndef PROTOSHOP_FILTER
#define PROTOSHOP_FILTER

#include "../image/image.hpp"
#include "strategy/strategy.hpp"
#include "kernel.hpp"

class Filter {
private:
  FilterStrategyBase* strategy;
public:
  Filter(KernelType kernelType);

  /**
   * @method apply
   * @param {Image*} target of the filter
   */
  void apply(Image* target);
};

#endif
