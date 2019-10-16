#ifndef GRAYSCALE_IMAGE_HPP
#define GRAYSCALE_IMAGE_HPP

#include "base.hpp"

class GrayscaleImage : public Image {
private:
  static GrayscaleImage* loadPGMAscii(char* bytes, int size);
  static GrayscaleImage* loadPGMBinary(char* bytes, int size);
public:
  GrayscaleImage(int height, int width) : Image(GRAYSCALE, height, width) { }
  /**
   * @method loadPGM
   * @param {std::string} filename the name of the file to be loaded
   */
  static GrayscaleImage* loadPGM(std::string filename);
  static GrayscaleImage* loadRAW(std::string filename);
};

#endif
