#ifndef PROTOSHOP_ADJUSTMENT_INVERSE
#define PROTOSHOP_ADJUSTMENT_INVERSE

#include "base.hpp"

class AdjustmentInverse : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target the image that will be inversed
   * @desc all pixel will be the inverse = (255 - p)
   */
  static void apply(Image* target);
};

#endif
