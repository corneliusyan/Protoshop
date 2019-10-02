#ifndef PROTOSHOP_ADJUSTMENT_FLIP
#define PROTOSHOP_ADJUSTMENT_FLIP

#include "base.hpp"

class AdjustmentFlip : public Adjustment {
public:
  static void verticalFlip(Image* target);
  static void horizontalFlip(Image* target);
};

#endif
