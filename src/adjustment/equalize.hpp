#ifndef PROTOSHOP_ADJUSTMENT_HISTOGRAMEQUALIZE
#define PROTOSHOP_ADJUSTMENT_HISTOGRAMEQUALIZE

#include "../image/image.hpp"
#include "base.hpp"

int** createHistogramDistribution(Image* source);

class AdjustmentHistogramEqualize : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target of the adjustment
   */
  static void apply(Image* target);
};

class AdjustmentHistogramSpecification : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target of the adjustment
   */
  static void apply(Image* target, Image* specification);
};

#endif
