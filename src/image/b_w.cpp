#include <fstream>
#include <iostream>
#include "exception.hpp"
#include "b_w.hpp"

BWImage* BWImage::loadPBM(std::string filename) {
  std::ifstream image_file;
  image_file.open(filename, std::ios::in | std::ios::binary);
  if (image_file.is_open()) {
    std::streampos size = image_file.tellg();
    char* memblock = new char[size];
    image_file.seekg(0, std::ios::beg);
    image_file.read(memblock, size);
    image_file.close();

    delete[] memblock;

    return NULL;
  } else {
    throw ImageLoadException("Cannot open image file");
  }
}
