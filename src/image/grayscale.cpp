#include <iostream>
#include <fstream>
#include "grayscale.hpp"
#include "exception.hpp"
#include "../utils/reader.hpp"

GrayscaleImage* GrayscaleImage::loadPGMAscii(char *bytes, int size) {
  int pointer = 0;
  std::string signature = nextString(bytes, size, &pointer);
  int width = nextInt(bytes, size, &pointer);
  int height = nextInt(bytes, size, &pointer);
  int maxValue = nextInt(bytes, size, &pointer);

  GrayscaleImage* image = new GrayscaleImage(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uchar gray = (int) ((nextInt(bytes, size, &pointer) * 1.0 / maxValue) * 255) & 0xFF;
      image->set_pixel(i, j, pixel(gray));
    }
  }
  return image;
}

GrayscaleImage* GrayscaleImage::loadPGMBinary(char *bytes, int size) {
  int pointer = 0;
  std::string signature = nextString(bytes, size, &pointer);
  int width = nextInt(bytes, size, &pointer);
  std::cout << width << std::endl;
  int height = nextInt(bytes, size, &pointer);
  int maxValue = nextInt(bytes, size, &pointer);
  std::cout << maxValue << std::endl;

  GrayscaleImage* image = new GrayscaleImage(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uchar gray = bytes[pointer];
      image->set_pixel(i, j, pixel(gray));
      pointer += 1;
    }
  }
  return image;
}

GrayscaleImage* GrayscaleImage::loadPGM(std::string filename) {
  std::ifstream image_file;
  image_file.open(filename, std::ios::in | std::ios::binary);
  if (image_file.is_open()) {
    // retrieving file size
    image_file.seekg(0, std::ios::end);
    std::streampos size = image_file.tellg();
    image_file.seekg(0, std::ios::beg);

    char* bytes = new char[size];
    image_file.read(bytes, size);
    image_file.close();

    GrayscaleImage* image;
    bool headerRecogized = false;

    if (bytes[0] == 'P' && bytes[1] == '2') {
      image = loadPGMAscii(bytes, size);
      headerRecogized = true;
    } else if (bytes[0] == 'P' && bytes[1] == '5') {
      std::cout << "binary" << std::endl;
      image = loadPGMBinary(bytes, size);
      headerRecogized = true;
    }

    delete[] bytes;

    if (!headerRecogized) {
      throw ImageLoadException("Image header not recognized");
    }

    return image;
  } else {
    throw ImageLoadException("Cannot open image file");
  }
}
