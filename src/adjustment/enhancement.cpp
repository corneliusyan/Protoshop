#include "enhancement.h"

void AdjustmentEnhancement::brighten(Image *target, double multiplier) {  
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      target->set_pixel(i, j, px * multiplier);
    }
  }
}

void AdjustmentEnhancement::contrastStretch(Image* target, int rMin, int rMax) {

}

void AdjustmentEnhancement::log(Image* target, double c) {

}

void AdjustmentEnhancement::inverseLog(Image* target, double c) {

}

void AdjustmentEnhancement::power(Image* target, double c) {

}

void AdjustmentEnhancement::graySlicing(Image* target, int rMin, int rMax) {

}

void AdjustmentEnhancement::bitSlicing(Image* target) {

}

