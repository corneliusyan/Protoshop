#ifndef PROTOSHOP_ADJUSTMENT_TRANSLATE
#define PROTOSHOP_ADJUSTMENT_TRANSLATE

#include "base.hpp"

class AdjustmentTranslate : public Adjustment {
public:
  static void apply(Image* target, int m, int n);
};

#endif
