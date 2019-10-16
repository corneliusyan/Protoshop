#ifndef PROTOSHOP_ADJUSTMENT_HISTOGRAMEQUALIZE
#define PROTOSHOP_ADJUSTMENT_HISTOGRAMEQUALIZE

#include "../image/image.hpp"
#include "base.hpp"

class AdjustmentHistogramEqualize : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target of the adjustment
   */
  static void apply(Image* target);
};

#endif
