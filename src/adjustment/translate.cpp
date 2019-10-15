#include "translate.hpp"

void AdjustmentTranslate::apply(Image* target, int m, int n) {
  Image* img = new Image(*target);
  int N = img->height, M = img->width;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int target_row = i-m, target_column = j-n;
      if (target_row >= M || target_row < 0 || target_column >= N || target_column < 0) {
        target->set_black(i, j);
      } else {
        target->set_pixel(i, j, img->get_pixel(target_row, target_column));
      }
    }
  }
}
