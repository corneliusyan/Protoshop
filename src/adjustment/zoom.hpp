#ifndef PROTOSHOP_ADJUSTMENT_ZOOM
#define PROTOSHOP_ADJUSTMENT_ZOOM

#include "base.hpp"

class AdjustmentZoom : public Adjustment {
public:
  static void zoomOut(Image* target);
  static void zoomIn(Image* target);
};

#endif
