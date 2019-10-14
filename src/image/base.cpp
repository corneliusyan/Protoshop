#include <QtWidgets>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QPrintDialog>

#include <cstdlib>
#include <iostream>
#include "../utils/string.hpp"
#include "b_w.hpp"
#include "base.hpp"
#include "exception.hpp"
#include "grayscale.hpp"
#include "pixel.hpp"
#include "r_g_b.hpp"

Image::Image() {
    this->imageType = ImageType::RGB;
    this->height = 32;
    this->width = 32;

    this->pixels = (pixel**) malloc(height * sizeof (pixel*));
    for (int i = 0; i < height; i++) {
      this->pixels[i] = (pixel*) malloc(width * sizeof (pixel));
      for (int j = 0; j < width; j++) {
        this->pixels[i][j] = pixel(0, 0, 0, 0);
      }
    }

    this->qimg = new QImage();
}

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
  QImage::Format qt_format;
  switch (imageType) {
    case BLACKWHITE:
    case GRAYSCALE:
      depth = 1;
      qt_format = QImage::Format_Grayscale8;
      break;
    case RGB:
      depth = 3;
      qt_format = QImage::Format_RGB32;
      break;
  }

  this->qimg = new QImage(width, height, qt_format);
  this->qimg->fill(0);
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
  QRgb value;

  if (px.len == 1) {
      value = qRgb(px.in[0], px.in[0], px.in[0]);
      (*this->qimg).setPixel(col, row, value);
  } else {
      value = qRgb(px.in[0], px.in[1], px.in[2]);
      // std::cout << px.in[0] << " " << px.in[1] << " " << px.in[2] << std::endl;
      (*this->qimg).setPixel(col, row, value);
  }
}

pixel Image::get_pixel(int row, int col) {
  return this->pixels[row][col];
}

void Image::show() {

}

QImage Image::getQImage() {
    if ((*this->qimg).isNull()) {
        std::cout << "null ewe" << std::endl;
    }
    return (*this->qimg);
}

Image& Image::operator=(const Image& other) {
    this->qimg = other.qimg;
    this->width = other.width;
    this->height = other.height;
    this->imageType = other.imageType;
    this->pixels = (pixel**) malloc(height * sizeof (pixel*));
    for (int i = 0; i < height; i++) {
      this->pixels[i] = (pixel*) malloc(width * sizeof (pixel));
      for (int j = 0; j < width; j++) {
        this->pixels[i][j] = other.pixels[i][j];
      }
    }
    return (*this);
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




