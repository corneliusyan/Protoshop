#include <algorithm>
#include "equalize.hpp"
#include "../utils/math.hpp"

int** createHistogramDistribution(Image* source) {
  int pxlen = source->get_pixel(0, 0).len;
  int** probs = new int*[pxlen];
  for (int k = 0; k < pxlen; k++) {
    probs[k] = new int[256];
    for (int i = 0; i < 256; i++) {
      probs[k][i] = 0;
    }
  }

  for (int i = 0; i < source->height; i++) {
    for (int j = 0; j < source->width; j++) {
      pixel px = source->get_pixel(i, j);
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

  return probs;
}

void AdjustmentHistogramEqualize::apply(Image* target) {
  int pxlen = target->get_pixel(0, 0).len;
  int** probs = createHistogramDistribution(target);

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

void AdjustmentHistogramSpecification::apply(Image* target, Image* specification) {
  int pxlen = target->get_pixel(0, 0).len;
  int** probsTarget = createHistogramDistribution(target);
  int** probsSpecification = createHistogramDistribution(specification);
  int** conversionTarget = new int*[pxlen];
  int** conversionSpecification = new int*[pxlen];
  for (int k = 0; k < pxlen; k++) {
    conversionTarget[k] = new int[256];
    conversionSpecification[k] = new int[256];

    for (int j = 0; j < 256; j++) {
      conversionTarget[k][j] = 0;
      conversionSpecification[k][j] = 0;
    }
  }

  int dimen = target->width * target->height;
  for (int k = 0; k < pxlen; k++) {
    for (int i = 0; i < 256; i++) {
      int newValSpecification = clip((int) probsSpecification[0][i] * 255 / dimen, 0, 255);
      conversionSpecification[k][newValSpecification] = i;
    }
    for (int i = 1; i < 256; i++) {
      conversionSpecification[k][i] = std::max(conversionSpecification[k][i], conversionSpecification[k][i - 1]);
    }
  }

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel px;
      pixel ori = target->get_pixel(i, j);
      if (pxlen == 3) {
        px = pixel(
          conversionSpecification[0][clip((int) probsTarget[0][ori.in[0]] * 255 / dimen, 0, 255)],
          conversionSpecification[1][clip((int) probsTarget[1][ori.in[1]] * 255 / dimen, 0, 255)],
          conversionSpecification[2][clip((int) probsTarget[2][ori.in[2]] * 255 / dimen, 0, 255)]
        );
      } else {
        px = pixel(
          conversionSpecification[0][clip((int) probsTarget[0][ori.in[0]] * 255 / dimen, 0, 255)]
        );
      }
      target->set_pixel(i, j, px);
    }
  }

  for (int k = 0; k < pxlen; k++) {
    delete[] probsTarget[k];
    delete[] probsSpecification[k];
  }
  delete[] probsTarget;
  delete[] probsSpecification;
  delete[] conversionTarget;
  delete[] conversionSpecification;
}
