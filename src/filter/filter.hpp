#ifndef PROTOSHOP_FILTER
#define PROTOSHOP_FILTER

#include "../image/image.hpp"
#include "kernel.hpp"
#include "strategy.hpp"

class Filter {
private:
  FilterStrategy* strategy;
public:
  Filter(KernelType kernelType);

  /**
   * @method apply
   * @param {Image*} target of the filter
   */
  void apply(Image* target);
};

#endif
