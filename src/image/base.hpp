#ifndef BASE_IMAGE_HPP
#define BASE_IMAGE_HPP

#include <iostream>
#include "pixel.hpp"

enum ImageType {
    BLACKWHITE,
    GRAYSCALE,
    RGB
};

class Image {
protected:
  pixel** pixels;

public:
  ImageType imageType;
  int height;
  int width;

  /**
   * @constructor
   * @param {ImageType} imageType type of the image
   * @param {int} height height of the image
   * @param {int} width width of the image
   */
  Image(ImageType imageType, int height, int width);

  /**
   * @constructor
   * @param {string} filename of the image file
   */
  static Image load(std::string filename);

  ~Image();
};

#endif
