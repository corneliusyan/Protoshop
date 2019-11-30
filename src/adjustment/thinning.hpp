#ifndef PROTOSHOP_ADJUSTMENT_THINNING
#define PROTOSHOP_ADJUSTMENT_THINNING

#include "base.hpp"

class AdjustmentThinning : public Adjustment {
public:
  static void apply(Image* target);
};

#endif
