#ifndef R_G_B_IMAGE_HPP
#define R_G_B_IMAGE_HPP

#include "base.hpp"

class RGBImage : Image {
private:
  /**
   * @var r matrix of pixels red intensity
   */
  unsigned char** r;

  /**
   * @var g matrix of pixels green intensity
   */
  unsigned char** g;

  /**
   * @var b matrix of pixels blue intensity
   */
  unsigned char** b;

public:
  /**
   * @param {int} height height of the image
   * @param {int} width width of the image
   * @param {unsigned char**} r matrix of pixels red intensity
   * @param {unsigned char**} g matrix of pixels green intensity
   * @param {unsigned char**} b matrix of pixels blue intensity
   */
  RGBImage(int height, int width, unsigned char** r, unsigned char** g, unsigned char** b);

  ~RGBImage();
};

#endif
