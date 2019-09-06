#include <cstdio>
#include <cstdlib>
#include "base.hpp"

Image::Image(ImageType imageType, int height, int width) {
  this->imageType = imageType;
  this->height = height;
  this->width = width;

  this->pixels = (pixel**) malloc(height * sizeof (pixel*));
  for (int i = 0; i < height; i++) {
    this->pixels[i] = (pixel*) malloc(width * sizeof (pixel));
  }
}

Image::~Image() {
  for (int i = 0; i < this->height; i++) {
    delete this->pixels[i];
  }
  delete this->pixels;
}
