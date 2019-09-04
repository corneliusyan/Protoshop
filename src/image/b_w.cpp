#include "b_w.hpp"

BWImage::BWImage(int height, int width, unsigned char** in)
  : Image(BLACKWHITE, height, width) {
  this->in = new unsigned char*[height];

  for (int i = 0; i < height; i++) {
    this->in[i] = new unsigned char[width];

    for (int j = 0; i < width; j++) {
      this->in[i][j] = in[i][j];
    }
  }
}

BWImage::~BWImage() {
  for (int i = 0; i < this->height; i++) {
    delete this->in[i];
  }
  delete this->in;
}
