#ifndef PROTOSHOP_ADJUSTMENT_BINARIZE
#define PROTOSHOP_ADJUSTMENT_BINARIZE

#include "base.hpp"

class AdjustmentBinarize : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target the image that will be binarize
   * @desc all pixel that has lower intensity than treshold will be turned into 0
   * and the rest will be turned into 1
   */
  static void applyBinarize(Image* target, int treshold);
  static void applyAverage(Image* target);
};

#endif
