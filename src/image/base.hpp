#ifndef BASE_IMAGE_HPP
#define BASE_IMAGE_HPP

enum ImageType {
    BLACKWHITE,
    GRAYSCALE,
    RGB
};

class Image {
private:

public:
  ImageType imageType;
  int height;
  int width;

  /**
   * @constructor
   * @param {ImageType} imageType type of the image
   */
  Image(ImageType imageType);

  /**
   * @constructor
   * @param {ImageType} imageType type of the image
   * @param {int} height height of the image
   * @param {int} width width of the image
   */
  Image(ImageType imageType, int height, int width);

  /**
   * @constructor
   * @param {char*} filename of the image file
   */
  Image(char* filename);
};

#endif
