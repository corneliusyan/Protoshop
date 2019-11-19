#ifndef BASE_IMAGE_HPP
#define BASE_IMAGE_HPP

#include <QImage>
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

private:
  QImage* qimg;

public:
  ImageType imageType;
  int height;
  int width;
  bool isFourierEmpty;

  double **r_imaginer;
  double **r_real;
  double **g_imaginer;
  double **g_real;
  double **b_imaginer;
  double **b_real;

  /**
   * @constructor
   * @param {ImageType} imageType type of the image
   * @param {int} height height of the image
   * @param {int} width width of the image
   */
  Image(ImageType imageType, int height, int width);

  Image(const Image& other);

  Image();

  /**
   * @constructor
   * @param {string} filename of the image file
   */
  static Image* load(std::string filename);

  /**
   * @method set_black
   * @param {int} row position of pixel from top, starting from 0
   * @param {int} col position of pixel from left, starting from 0
   * change pixel[row][col] into a black pixel, according to imageType
   */
  void set_black(int row, int col);

  /**
   * @method set_pixel
   * @param {int} row position of pixel from top, starting from 0
   * @param {int} col position of pixel from left, starting from 0
   * @param {pixel} px new pixel
   */
  void set_pixel(int row, int col, pixel px);

  /**
   * @method get_pixel
   * @param {int} row position of pixel from top, starting from 0
   * @param {int} col position of pixel from left, starting from 0
   */
  pixel get_pixel(int row, int col);

  /**
   * @method show
   * show the image using CImg library
   */
  void show();

  virtual ~Image();

  QImage getQImage();
  Image& operator=(const Image& other);
  Image* operator+(const Image& other);
  Image* operator*(const Image& other);
  Image* operator+(int scalar);
  Image* operator-(int scalar);
  Image* operator*(int scalar);
  Image* operator/(int scalar);
  Image* operator&(const Image& other);
  Image* operator|(const Image& other);
  Image* operator!(void);
};

#endif
