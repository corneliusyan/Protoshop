#ifndef B_W_IMAGE_HPP
#define B_W_IMAGE_HPP

#include "base.hpp"

class BWImage : public Image {
private:
  static BWImage* loadPBMAscii(char* bytes, int size);
  static BWImage* loadPBMBinary(char* bytes, int size);

public:
  BWImage(int height, int width) : Image(BLACKWHITE, height, width) { }
  /**
   * @method loadPPM
   * @param {std::string} filename the name of the file to be loaded
   */
  static BWImage* loadPBM(std::string filename);
};

#endif
