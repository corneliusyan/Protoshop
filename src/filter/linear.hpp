#ifndef PROTOSHOP_FILTER_LINEAR
#define PROTOSHOP_FILTER_LINEAR

#include <vector>
#include "base.hpp"

class FilterLinear : public FilterBase {
public:
  /**
   * @method getKernel
   * @param {Kernel} kernel
   */
  virtual Kernel getKernel() = 0;
  virtual void apply(Image* target);
};

class FilterGaussian : public FilterLinear {
public:
  virtual Kernel getKernel();
};

#endif
