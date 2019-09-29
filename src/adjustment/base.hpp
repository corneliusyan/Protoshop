#ifndef PROTOSHOP_ADJUSTMENT_BASE
#define PROTOSHOP_ADJUSTMENT_BASE

#include "../image/image.hpp"

class Adjustment {
public:
  /**
   * @method apply
   * @param {Image*} target of the adjustment
   */
  static void apply(Image* target);
};

#endif
