#include "flip.hpp"

void AdjustmentFlip::verticalFlip(Image* target) {
  Image* img = new Image(*target);
  int N = img->height, M = img->width;

  int k = M - 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      target->set_pixel(k, j, img->get_pixel(i, j));
    }
    k--;
  }
}

void AdjustmentFlip::horizontalFlip(Image* target) {
  Image* img = new Image(*target);
  int N = img->height, M = img->width;

  int k = M - 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      target->set_pixel(i, k-j, img->get_pixel(i, j));
    }
  }
}
