#include "hough.hpp"
#include "src/image/base.hpp"
#include <math.h>

Image* Hough::transform(Image* target) {

  double PI = 3.1415926535897932384626433832795;

  // rescaling
  int min = 0;
  int max = 0;
  int lower = 0;
  int upper = 255;
  
  int height = target->height;
  int width = target->width;

  int centerX = (int)width/2;
  int centerY = (int)height/2;
  int maxTheta = 180;

  int houghHeight = (int)(sqrt(2) * std::max(width, height)) / 2;
  int doubleHeight = houghHeight * 2;
  int houghHeightHalf = houghHeight / 2;
  int houghWidthHalf = maxTheta / 2;

  int houghMap[doubleHeight][maxTheta];
  int scaled[doubleHeight][maxTheta];

  // initialize
  for (int i = 0; i < doubleHeight; i++) {
    for (int j = 0; j < maxTheta; j++) {
      houghMap[i][j] = 0;
      scaled[i][j] = 0;
    }
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      pixel p = target->get_pixel(y, x);
      if (p.in[0] != 0) {
        for (int theta = 0; theta < maxTheta; theta++) {
          double rad = theta * PI / 180;
          int rho = (int)(((x - centerX) * cos(rad)) + ((y - centerY) * sin(rad)));
          rho += houghHeight;
          if ((rho > 0) && (rho <= doubleHeight)) {
            houghMap[rho][theta]++;
          }
        }
      }
    }
  }

  // rescale map
  for (int i = 0; i < doubleHeight; i++) {
    for (int j = 0; j < maxTheta; j++) {
      min = std::min(min, houghMap[i][j]);
      max = std::max(max, houghMap[i][j]);
    }
  }

  for (int i = 0; i < doubleHeight; i++) {
    for (int j = 0; j < maxTheta; j++) {
      scaled[i][j] = (int)(upper - lower) * (houghMap[i][j] - min) / (max - min) + lower;
    }
  }

  // assign to target to be returned
  target = new Image(RGB, doubleHeight, maxTheta);
  for (int i = 0; i < doubleHeight; i++) {
    for (int j = 0; j < maxTheta; j++) {
      pixel p = pixel(scaled[i][j], scaled[i][j], scaled[i][j]);
      target->set_pixel(i, j, p);
    }
  }

  return target;
}
