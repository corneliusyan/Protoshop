#include <cstdlib>
#include "../utils/string.hpp";
#include "b_w.hpp"
#include "base.hpp"
#include "exception.hpp"
#include "grayscale.hpp"
#include "pixel.hpp"
#include "r_g_b.hpp"

Image::Image(ImageType imageType, int height, int width) {
  this->imageType = imageType;
  this->height = height;
  this->width = width;

  this->pixels = (pixel**) malloc(height * sizeof (pixel*));
  for (int i = 0; i < height; i++) {
    this->pixels[i] = (pixel*) malloc(width * sizeof (pixel));
    for (int j = 0; j < width; j++) {
      this->pixels[i][j] = pixel(0, 0, 0, 0);
    }
  }
}

Image::~Image() {
  for (int i = 0; i < this->height; i++) {
    free(this->pixels[i]);
  }
  free(this->pixels);
}

Image Image::load(std::string filename) {
  if (hasEnding(filename, ".pbm")) {
    return BWImage::loadPBM(filename);
  } else if (hasEnding(filename, ".pgm")) {
    return GrayscaleImage::loadPGM(filename);
  } else if (hasEnding(filename, ".ppm")) {
    return RGBImage::loadPPM(filename);
  } else if (hasEnding(filename, ".bmp")) {
    return RGBImage::loadBMP(filename);
  } else {
    throw ImageLoadException("format not supported");
  }
}
