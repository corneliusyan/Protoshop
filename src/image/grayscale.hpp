#ifndef GRAYSCALE_IMAGE_HPP
#define GRAYSCALE_IMAGE_HPP

#include "base.hpp"

class GrayscaleImage : public Image {
public:
  /**
   * @method loadPGM
   * @param {std::string} filename the name of the file to be loaded
   */
  static GrayscaleImage* loadPGM(std::string filename);
};

#endif
