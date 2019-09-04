#ifndef B_W_IMAGE_HPP
#define B_W_IMAGE_HPP

#include "base.hpp"

class BWImage : Image {
private:
  /**
   * @var in matrix of pixels intensity (0 = black, 255 = white)
   */
  unsigned char** in;

public:
  /**
   * @param {int} height height of the image
   * @param {int} width width of the image
   * @param {unsigned char**} matrix of pixels intensity (0 or 255)
   */
  BWImage(int height, int width, unsigned char** in);

  ~BWImage();
};

#endif
