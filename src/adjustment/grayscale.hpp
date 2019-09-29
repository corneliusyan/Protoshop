#ifndef PROTOSHOP_ADJUSTMENT_GRAYSCALE
#define PROTOSHOP_ADJUSTMENT_GRAYSCALE

#include "base.hpp"

class AdjustmentGrayscale : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target the image that will be grayscaled
   * @desc all pixel will be convert to grayscale with formul
   *       0.2126 R + 0.7152 G + 0.0722 B (for RGB)
   *       https://en.wikipedia.org/wiki/Luma_(video)
   */
  static void apply(Image* target);
};

#endif
