#ifndef B_W_IMAGE_HPP
#define B_W_IMAGE_HPP

#include "base.hpp"

class BWImage : public Image {
public:
  /**
   * @method loadPPM
   * @param {std::string} filename the name of the file to be loaded
   */
  static BWImage* loadPBM(std::string filename);
};

#endif
