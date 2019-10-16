#include "equalize.hpp"
#include "../utils/math.hpp"

void AdjustmentHistogramEqualize::apply(Image* target) {
  int pxlen = target->get_pixel(0, 0).len;
  int** probs = new int*[pxlen];
  for (int k = 0; k < pxlen; k++) {
    probs[k] = new int[256];
    for (int i = 0; i < 256; i++) {
      probs[k][i] = 0;
    }
  }

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px = target->get_pixel(i, j);
      for (int k = 0; k < px.len; k++) {
        probs[k][px.in[k]] += 1;
      }
    }
  }

  for (int k = 0; k < pxlen; k++) {
    for (int i = 1; i < 256; i++) {
      probs[k][i] += probs[k][i - 1];
    }
  }

  int dimen = target->width * target->height;
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px;
      pixel ori = target->get_pixel(i, j);
      if (pxlen == 3) {
        px = pixel(
          clip((int) probs[0][ori.in[0]] * 255 / dimen, 0, 255),
          clip((int) probs[1][ori.in[1]] * 255 / dimen, 0, 255),
          clip((int) probs[2][ori.in[2]] * 255 / dimen, 0, 255)
        );
      } else {
        px = pixel(
          clip((int) probs[0][ori.in[0]] * 255 / dimen, 0, 255)
        );
      }
      target->set_pixel(i, j, px);
    }
  }

  for (int k = 0; k < pxlen; k++) {
    delete[] probs[k];
  }
  delete[] probs;
}
