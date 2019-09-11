#include <fstream>
#include "exception.hpp"
#include "../utils/reader.hpp"
#include "r_g_b.hpp"

RGBImage* RGBImage::loadPPMAscii(char* bytes, int size) {
  int pointer = 0;
  std::string signature = nextString(bytes, size, &pointer);
  int width = nextInt(bytes, size, &pointer);
  int height = nextInt(bytes, size, &pointer);
  int maxValue = nextInt(bytes, size, &pointer);

  RGBImage* image = new RGBImage(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uchar r = (int) ((nextInt(bytes, size, &pointer) * 1.0 / maxValue) * 255) & 0xFF;
      uchar g = (int) ((nextInt(bytes, size, &pointer) * 1.0 / maxValue) * 255) & 0xFF;
      uchar b = (int) ((nextInt(bytes, size, &pointer) * 1.0 / maxValue) * 255) & 0xFF;
      image->set_pixel(i, j, pixel(r, g, b));
    }
  }
  return image;
}

RGBImage* RGBImage::loadPPMBinary(char* bytes, int size) {
  int pointer = 0;
  std::string signature = nextString(bytes, size, &pointer);
  int width = nextInt(bytes, size, &pointer);
  int height = nextInt(bytes, size, &pointer);
  int maxValue = nextInt(bytes, size, &pointer);

  RGBImage* image = new RGBImage(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      uchar r = bytes[pointer];
      uchar g = bytes[pointer + 1];
      uchar b = bytes[pointer + 2];
      image->set_pixel(i, j, pixel(r, g, b));
      pointer += 3;
    }
  }
  return image;
}

RGBImage* RGBImage::loadPPM(std::string filename) {
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

    RGBImage* image;
    bool headerRecogized = false;

    if (bytes[0] == 'P' && bytes[1] == '3') {
      image = loadPPMAscii(bytes, size);
      headerRecogized = true;
    } else if (bytes[0] == 'P' && bytes[1] == '6') {
      image = loadPPMBinary(bytes, size);
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

RGBImage* RGBImage::loadBMP(std::string filename) {
  return NULL;
}
