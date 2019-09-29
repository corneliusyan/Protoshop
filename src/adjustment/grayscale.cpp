#include "grayscale.hpp"

void AdjustmentGrayscale::apply(Image* target) {
  if (target->imageType == RGB) {
    for (int i = 0; i < target->height; i++) {
      for (int j = 0; j < target->width; j++) {
        pixel px = target->get_pixel(i, j);
        uchar gray_level = (
          0.2126 * px.in[0] +
          0.7152 * px.in[1] +
          0.0722 * px.in[2]
        );
        pixel new_pixel = pixel(gray_level, gray_level, gray_level);
        target->set_pixel(i, j, new_pixel);
      }
    }
  }
}
