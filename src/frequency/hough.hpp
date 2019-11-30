#ifndef PROTOSHOP_FREQUENCY_HOUGH
#define PROTOSHOP_FREQUENCY_HOUGH

#include "../image/image.hpp"

class Hough {
public:
  /**
   * @method transform
   * @param {*Image} image to be transformed
   */
  static Image* transform(Image* target);
};

#endif
