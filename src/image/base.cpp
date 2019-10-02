#include <cstdlib>
#include <iostream>
#include "../../lib/CImg/CImg.h"
#include "../utils/string.hpp"
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

  int depth = 0;
  switch (imageType) {
    case BLACKWHITE:
    case GRAYSCALE:
      depth = 1;
      break;
    case RGB:
      depth = 3;
      break;
  }
  this->cimg = new cimg_library::CImg<unsigned char>(height, width, 1, depth);
  this->cimg->fill(0);
}

Image::Image(const Image& other) {
  Image img(other.imageType, other.height, other.width);

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      img.set_pixel(i, j, other.pixels[i][j]);
    }
  }
  *this = img;
}

Image::~Image() {
  for (int i = 0; i < this->height; i++) {
    free(this->pixels[i]);
  }
  free(this->pixels);
}

Image* Image::load(std::string filename) {
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

void Image::set_black(int row, int col) {
  switch (imageType) {
    case BLACKWHITE:
    case GRAYSCALE:
      set_pixel(row, col, pixel(0));
      break;
    case RGB:
      set_pixel(row, col, pixel(0, 0, 0));
      break;
  }
}

void Image::set_pixel(int row, int col, pixel px) {
  this->pixels[row][col] = px;
  for (int i = 0; i < px.len; i++) {
    (*this->cimg)(col, row, 0, i) = px.in[i];
  }
}

pixel Image::get_pixel(int row, int col) {
  return this->pixels[row][col];
}

void Image::show() {
  this->cimg->display("Image");
}

Image* Image::operator+(const Image& other) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] + other.pixels[i][j]);
    }
  }
  return img;
}

Image* Image::operator*(const Image& other) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] * other.pixels[i][j]);
    }
  }
  return img;
}

Image* Image::operator+(int scalar) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] + scalar);
    }
  }
  return img;
}


Image* Image::operator-(int scalar) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] - scalar);
    }
  }
  return img;
}


Image* Image::operator*(int scalar) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] * scalar);
    }
  }
  return img;
}


Image* Image::operator/(int scalar) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] / scalar);
    }
  }
  return img;
}

Image* Image::operator&(const Image& other) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] & other.pixels[i][j]);
    }
  }
  return img;
}

Image* Image::operator|(const Image& other) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, img->pixels[i][j] | other.pixels[i][j]);
    }
  }
  return img;
}


Image* Image::operator!(void) {
  Image* img = new Image(*this);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->set_pixel(i, j, !(img->pixels[i][j]));
    }
  }
  return img;
}




