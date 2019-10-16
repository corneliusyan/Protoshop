#include <math.h>
#include "fourier.hpp"
#include "src/adjustment/adjustment.hpp"

void Fourier::transform(Image* target) {
  int r_idx = 0, g_idx = 1, b_idx = 2;

  double PI = 3.1415926535897932384626433832795;

  if (target->imageType != ImageType::RGB) {
    g_idx = 0;
    b_idx = 0;
  }

  int height = target->height;
  int width = target->width;
  double r_amp[height][width];
  double g_amp[height][width];
  double b_amp[height][width];

  target->r_imaginer = (double**) malloc(height * sizeof (double*));
  target->r_real = (double**) malloc(height * sizeof (double*));
  target->g_imaginer = (double**) malloc(height * sizeof (double*));
  target->g_real = (double**) malloc(height * sizeof (double*));
  target->b_imaginer = (double**) malloc(height * sizeof (double*));
  target->b_real = (double**) malloc(height * sizeof (double*));
  for (int i = 0; i < height; i++) {
    target->r_imaginer[i] = (double*) malloc(width * sizeof (double));
    target->r_real[i] = (double*) malloc(width * sizeof (double));
    target->g_imaginer[i] = (double*) malloc(width * sizeof (double));
    target->g_real[i] = (double*) malloc(width * sizeof (double));
    target->b_imaginer[i] = (double*) malloc(width * sizeof (double));
    target->b_real[i] = (double*) malloc(width * sizeof (double));
    for (int j = 0; j < width; j++) {
      target->r_imaginer[i][j] = 0;
      target->r_real[i][j] = 0;
      target->g_imaginer[i][j] = 0;
      target->g_real[i][j] = 0;
      target->b_imaginer[i][j] = 0;
      target->b_real[i][j] = 0;
    }
  }

  for (int yWave = 0; yWave < height; yWave++) {
    for (int xWave = 0; xWave < width; xWave++) {
      for (int ySpace = 0; ySpace < height; ySpace++) {
        for (int xSpace = 0; xSpace < width; xSpace++) {
          pixel p = target->get_pixel(ySpace, xSpace);

          // Red Frequency
          target->r_real[yWave][xWave] += (p.in[r_idx] * cos(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          target->r_imaginer[yWave][xWave] -= (p.in[r_idx] * sin(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          r_amp[yWave][xWave] = sqrt(target->r_real[yWave][xWave] * target->r_real[yWave][xWave] + target->r_imaginer[yWave][xWave] * target->r_imaginer[yWave][xWave]);

          // Green Frequency
          target->g_real[yWave][xWave] += (p.in[g_idx] * cos(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          target->g_imaginer[yWave][xWave] -= (p.in[g_idx] * sin(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          g_amp[yWave][xWave] = sqrt(target->g_real[yWave][xWave] * target->g_real[yWave][xWave] + target->g_imaginer[yWave][xWave] * target->g_imaginer[yWave][xWave]);

          // Blue Frequency
          target->b_real[yWave][xWave] += (p.in[b_idx] * cos(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          target->b_imaginer[yWave][xWave] -= (p.in[b_idx] * sin(2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height)))) / sqrt(width * height);
          b_amp[yWave][xWave] = sqrt(target->b_real[yWave][xWave] * target->b_real[yWave][xWave] + target->b_imaginer[yWave][xWave] * target->b_imaginer[yWave][xWave]);
        }
      }
    }
    std::cout << yWave << std::endl;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      pixel p = pixel(r_amp[i][j], g_amp[i][j], b_amp[i][j]);
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

    double r_fr[height][width];
    double r_fi[height][width];
    double r_famp[height][width];
    double g_fr[height][width];
    double g_fi[height][width];
    double g_famp[height][width];
    double b_fr[height][width];
    double b_fi[height][width];
    double b_famp[height][width];

    for (int ySpace = 0; ySpace < height; ySpace++) {
      for (int xSpace = 0; xSpace < width; xSpace++) {
        for (int yWave = 0; yWave < height; yWave++) {
          for (int xWave = 0; xWave < width; xWave++) {

            double theta = 2 * PI * ((1.0 * xWave * xSpace / width) + (1.0 * yWave * ySpace / height));

            // Red Space
            r_fr[ySpace][xSpace] += (((target->r_real[yWave][xWave] * cos(theta)) - (target->r_imaginer[yWave][xWave] * sin(theta))) / sqrt(width * height));
            r_fi[ySpace][xSpace] += (((target->r_imaginer[yWave][xWave] * cos(theta)) + (target->r_real[yWave][xWave] * sin(theta))) / sqrt(width * height));
            r_famp[ySpace][xSpace] = sqrt(r_fr[ySpace][xSpace] * r_fr[ySpace][xSpace] + r_fi[ySpace][xSpace] * r_fi[ySpace][xSpace]);

            // Green Space
            g_fr[ySpace][xSpace] += (((target->g_real[yWave][xWave] * cos(theta)) - (target->g_imaginer[yWave][xWave] * sin(theta))) / sqrt(width * height));
            g_fi[ySpace][xSpace] += (((target->g_imaginer[yWave][xWave] * cos(theta)) + (target->g_real[yWave][xWave] * sin(theta))) / sqrt(width * height));
            g_famp[ySpace][xSpace] = sqrt(g_fr[ySpace][xSpace] * g_fr[ySpace][xSpace] + g_fi[ySpace][xSpace] * g_fi[ySpace][xSpace]);

            // Blue Space
            b_fr[ySpace][xSpace] += (((target->b_real[yWave][xWave] * cos(theta)) - (target->b_imaginer[yWave][xWave] * sin(theta))) / sqrt(width * height));
            b_fi[ySpace][xSpace] += (((target->b_imaginer[yWave][xWave] * cos(theta)) + (target->b_real[yWave][xWave] * sin(theta))) / sqrt(width * height));
            b_famp[ySpace][xSpace] = sqrt(b_fr[ySpace][xSpace] * b_fr[ySpace][xSpace] + b_fi[ySpace][xSpace] * b_fi[ySpace][xSpace]);
          }
        }
      }
      std::cout << ySpace << std::endl;
    }

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        pixel p = pixel(r_famp[i][j], g_famp[i][j], b_famp[i][j]);
        target->set_pixel(i, j, p);
      }
    }
  }
}
