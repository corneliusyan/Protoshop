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
  int range = rMax - rMin, depth=0;
  switch (target->imageType) {
    case BLACKWHITE:
    case GRAYSCALE:
      depth = 1;
      break;
    case RGB:
      depth = 3;
      break;
  }

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      for (int k = 0; k < depth; k++) {
        if (px.in[k] < rMin)
          px.in[k] = 0;
        else if (px.in[k] > rMax)
          px.in[k] = 255;
        else
          px.in[k] = (px.in[k] - rMin)*255/range;
      }
      target->set_pixel(i, j, px);
    }
  }
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

