#ifndef PROTOSHOP_ADJUSTMENT_ROTATE
#define PROTOSHOP_ADJUSTMENT_ROTATE

#include "base.hpp"

class AdjustmentRotate : public Adjustment {
public:
  static void rotate90CCW(Image* target);
  static void rotate90CW(Image* target);
};

#endif
