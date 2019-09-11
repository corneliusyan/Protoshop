#ifndef R_G_B_IMAGE_HPP
#define R_G_B_IMAGE_HPP

#include "base.hpp"

class RGBImage : public Image {
private:
  /**
   * @method loadPPMAscii
   * @desc load PPM fron bytes, treated as ascii data
   * @param {char[]} bytes of the image
   * @return {RGBImage*} Image loaded from the bytes
   */
  static RGBImage* loadPPMAscii(char* bytes, int size);

  /**
   * @method loadPPMBinary
   * @desc load PPM fron bytes, treated as binary data
   * @param {char[]} bytes of the image
   * @return {RGBImage*} Image loaded from the bytes
   */
  static RGBImage* loadPPMBinary(char* bytes, int size);

public:
  RGBImage(int height, int width) : Image(RGB, height, width) { }

  /**
   * @method loadPPM
   * @param {std::string} filename the name of the file to be loaded
   * @return {RGBImage*} Image loaded from the file
   */
  static RGBImage* loadPPM(std::string filename);

  /**
   * @method loadBMP
   * @param {std::string} filename the name of the file to be loaded
   * @return {RGBImage*} Image loaded from the file
   */
  static RGBImage* loadBMP(std::string filename);
};

#endif
