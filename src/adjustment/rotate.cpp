#include "rotate.hpp"

void AdjustmentRotate::rotate90CCW(Image* target) {
  Image* img = new Image(*target);
  int N = img->height, M = img->width;
  int k;

  for (int i = 0; i < N; i++) {
    k = M-1;
    for (int j = 0; j < M; j++) {
      target->set_pixel(k, i, img->get_pixel(i, j));
      k--;
    }
  }
  delete img;
}

void AdjustmentRotate::rotate90CW(Image* target) {

}
