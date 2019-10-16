#include "zoom.hpp"

void AdjustmentZoom::zoomOut(Image* target) {
  Image* img = new Image(*target);
  int N = img->height, M = img->width;

  int m, n;
  m = 0; n = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (m < M && n < N) {
        target->set_pixel(m, n, img->get_pixel(i, j));
        target->set_pixel(m, n+1, img->get_pixel(i, j));
        target->set_pixel(m+1, n, img->get_pixel(i, j));
        target->set_pixel(m+1, n+1, img->get_pixel(i, j));
        n += 2;
      }
    }
    m += 2;
    n = 0;
  }
}

void AdjustmentZoom::zoomIn(Image* target) {
  int N = target->height, M = target->width;

  int depth = 0;
  switch (target->imageType) {
    case BLACKWHITE:
    case GRAYSCALE:
      depth = 1;
      break;
    case RGB:
      depth = 3;
      break;
  }

  unsigned char temp[N/2][M/2][depth];
  int m, n;
  m = 0; n = 0;
  for (int i = 0; i < N; i+=2) {
    for (int j = 0; j < M; j+=2) {
      for (int k = 0; k < depth; k++) {
        int sum = 0;
        sum += target->get_pixel(i,j).in[k];
        sum += target->get_pixel(i,j+1).in[k];
        sum += target->get_pixel(i+1,j).in[k];
        sum += target->get_pixel(i+1,j+1).in[k];
        temp[i/2][j/2][k] = sum/4;
      }
    }
  }

  Image* img = new Image(target->imageType, N, M);
  switch(depth) {
    case 1:
      for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < M/2; j++) {
          img->set_pixel(i, j, pixel(temp[i][j][0]));
        }
      }
      break;
    case 3:
      for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < M/2; j++) {
          img->set_pixel(i, j, pixel(temp[i][j][0], temp[i][j][1], temp[i][j][2]));
        }
      }
      break;
  }
  *target = *img;
}
