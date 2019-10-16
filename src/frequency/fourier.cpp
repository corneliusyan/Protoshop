#include <math.h>
#include "fourier.hpp"
#include "src/adjustment/adjustment.hpp"

void Fourier::transform(Image* target) {

  double PI = 3.1415926535897932384626433832795;

  if (target->imageType == ImageType::RGB) {
    AdjustmentGrayscale::apply(target);
  }

  int height = target->height;
  int width = target->width;
  double amp[height][width];

  target->imaginer = (double**) malloc(height * sizeof (double*));
  target->real = (double**) malloc(height * sizeof (double*));
  for (int i = 0; i < height; i++) {
    target->imaginer[i] = (double*) malloc(width * sizeof (double));
    target->real[i] = (double*) malloc(width * sizeof (double));
    for (int j = 0; j < width; j++) {
      target->imaginer[i][j] = 0;
      target->real[i][j] = 0;
    }
  }

  for (int yWave = 0; yWave < height; yWave++) {
    for (int xWave = 0; xWave < width; xWave++) {
      for (int ySpace = 0; ySpace < height; ySpace++) {
        for (int xSpace = 0; xSpace < width; xSpace++) {
          pixel p = target->get_pixel(ySpace, xSpace);
          target->real[yWave][xWave] += (p.in[0] * cos(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          target->imaginer[yWave][xWave] -= (p.in[0] * sin(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          amp[yWave][xWave] = sqrt(target->real[yWave][xWave] * target->real[yWave][xWave] + target->imaginer[yWave][xWave] * target->imaginer[yWave][xWave]);
        }
      }
    }
    std::cout << yWave << std::endl;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      pixel p = pixel(amp[i][j]);
      target->set_pixel(i, j, p);
    }
  }

  target->isFourierEmpty = false;
}

void Fourier::inverse(Image* target) {
  double PI = 3.1415926535897932384626433832795;

  if (!(target->isFourierEmpty)) {
    int height = target->height;
    int width = target->width;

    double fr[height][width];
    double fi[height][width];
    double famp[height][width];

    for (int ySpace = 0; ySpace < height; ySpace++) {
      for (int xSpace = 0; xSpace < width; xSpace++) {
        for (int yWave = 0; yWave < height; yWave++) {
          for (int xWave = 0; xWave < width; xWave++) {
            double theta = 2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height));
            fr[ySpace][xSpace] += ((target->real[yWave][xWave] * cos(theta)) - (target->imaginer[yWave][xWave] * sin(theta)));
            fi[ySpace][xSpace] += ((target->imaginer[yWave][xWave] * cos(theta)) + (target->real[yWave][xWave] * sin(theta)));
            famp[ySpace][xSpace] = sqrt(fr[ySpace][xSpace] * fr[ySpace][xSpace] + fi[ySpace][xSpace] * fi[ySpace][xSpace]);
          }
        }
      }
      std::cout << ySpace << std::endl;
    }

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        pixel p = pixel(famp[i][j]);
        target->set_pixel(i, j, p);
      }
    }
  }
}
