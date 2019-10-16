#include <fstream>
#include <iostream>
#include "exception.hpp"
#include "b_w.hpp"
#include "../utils/reader.hpp"

BWImage* BWImage::loadPBMAscii(char *bytes, int size) {
  int pointer = 0;
  std::string signature = nextString(bytes, size, &pointer);
  int width = nextInt(bytes, size, &pointer);
  int height = nextInt(bytes, size, &pointer);

  BWImage* image = new BWImage(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uchar gray;
      if (nextInt(bytes, size, &pointer) == 0)
        gray = 255;
      else
        gray = 0;
      image->set_pixel(i, j, pixel(gray));
    }
  }
  return image;
}

BWImage* BWImage::loadPBM(std::string filename) {
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

    BWImage* image;
    bool headerRecogized = false;

    if (bytes[0] == 'P' && bytes[1] == '1') {
      image = loadPBMAscii(bytes, size);
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
