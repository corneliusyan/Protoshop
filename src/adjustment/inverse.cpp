#include "inverse.hpp"

void AdjustmentInverse::apply(Image* target) {
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      target->set_pixel(i, j, 255 - px);
    }
  }
}
