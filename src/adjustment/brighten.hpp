#ifndef PROTOSHOP_ADJUSTMENT_BRIGHTEN
#define PROTOSHOP_ADJUSTMENT_BRIGHTEN

#include "base.hpp"

class AdjustmentBrighten : public Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target the image that will be brightened
   * @desc all pixel will be added by b
   */
  static void apply(Image* target, int b);
};

#endif
