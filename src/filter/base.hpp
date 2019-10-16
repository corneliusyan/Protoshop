#ifndef PROTOSHOP_FILTER_BASE
#define PROTOSHOP_FILTER_BASE

#include <vector>
#include "../image/image.hpp"

#define Kernel std::vector<std::vector<double> >

class FilterBase {
public:
  FilterBase() { }

  /**
   * @method apply
   * @param {Image*} target of the filter
   */
  virtual void apply(Image* target) = 0;
};

#endif
