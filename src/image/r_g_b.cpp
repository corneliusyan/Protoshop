#include "r_g_b.hpp"

RGBImage::RGBImage(int height, int width, unsigned char** r, unsigned char** g, unsigned char** b)
  : Image(RGB, height, width) {
  this->r = new unsigned char*[height];
  this->g = new unsigned char*[height];
  this->b = new unsigned char*[height];

  for (int i = 0; i < height; i++) {
    this->r[i] = new unsigned char[width];
    this->g[i] = new unsigned char[width];
    this->b[i] = new unsigned char[width];

    for (int j = 0; i < width; j++) {
      this->r[i][j] = r[i][j];
      this->g[i][j] = g[i][j];
      this->b[i][j] = b[i][j];
    }
  }
}

RGBImage::~RGBImage() {
  for (int i = 0; i < this->height; i++) {
    delete this->r[i];
    delete this->g[i];
    delete this->b[i];
  }
  delete this->r;
  delete this->g;
  delete this->b;
}
