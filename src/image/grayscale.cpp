#include "grayscale.hpp"

GrayscaleImage::GrayscaleImage(int height, int width, unsigned char** in)
  : Image(GRAYSCALE, height, width) {
  this->in = new unsigned char*[height];

  for (int i = 0; i < height; i++) {
    this->in[i] = new unsigned char[width];

    for (int j = 0; i < width; j++) {
      this->in[i][j] = in[i][j];
    }
  }
}

GrayscaleImage::~GrayscaleImage() {
  for (int i = 0; i < this->height; i++) {
    delete this->in[i];
  }
  delete this->in;
}
