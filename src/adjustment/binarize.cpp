#include "binarize.hpp"
#include "grayscaling.hpp"

void AdjustmentBinarize::applyBinarize(Image* target, int treshold) {
  if (target->imageType != GRAYSCALE) {
    AdjustmentGrayscale::apply(target);
    target->imageType = GRAYSCALE;
  }

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      if (px.in[0] <= treshold)
        target->set_pixel(i, j, pixel());
      else
        target->set_pixel(i, j, pixel(255));
    }
  }
}

void AdjustmentBinarize::applyAverage(Image* target) {
  if (target->imageType != GRAYSCALE) {
    AdjustmentGrayscale::apply(target);
    target->imageType = GRAYSCALE;
  }

  int total = 0;
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      total += px.in[0];
    }
  }

  AdjustmentBinarize::applyBinarize(target, total/(target->height*target->width));
}
