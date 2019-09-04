#ifndef GRAYSCALE_IMAGE_HPP
#define GRAYSCALE_IMAGE_HPP

#include "base.hpp"

class GrayscaleImage : Image {
private:
  /**
   * @var in matrix of pixels intensity
   */
  unsigned char** in;

public:
  /**
   * @param {int} height height of the image
   * @param {int} width width of the image
   * @param {unsigned char**} in matrix of pixels intensity
   */
  GrayscaleImage(int height, int width, unsigned char** in);

  ~GrayscaleImage();
};

#endif
