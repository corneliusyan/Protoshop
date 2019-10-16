#ifndef PROTOSHOP_FILTER_FOURIER
#define PROTOSHOP_FILTER_FOURIER

#include <vector>
#include "base.hpp"

class FilterFourier : public FilterBase {
public:
  /**
   * @method getKernel
   * @param {Kernel} kernel
   */
  virtual void apply(Image* target);
  virtual void applyInverse(Image* target);
};

#endif
