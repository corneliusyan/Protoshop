#ifndef R_G_B_IMAGE_HPP
#define R_G_B_IMAGE_HPP

#include "base.hpp"

class RGBImage : public Image {
public:
  /**
   * @method loadPPM
   * @param {std::string} filename the name of the file to be loaded
   */
  static RGBImage* loadPPM(std::string filename);

  /**
   * @method loadBMP
   * @param {std::string} filename the name of the file to be loaded
   */
  static RGBImage* loadBMP(std::string filename);
};

#endif
