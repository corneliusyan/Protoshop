#include <cstdio>
#include <cstdlib>
#include "base.hpp"

Image::Image(ImageType imageType, int height, int width) {
  this->imageType = imageType;
  this->height = height;
  this->width = width;
}
