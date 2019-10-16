#ifndef PROTOSHOP_FREQUENCY_FOURIER
#define PROTOSHOP_FREQUENCY_FOURIER

#include "../image/image.hpp"

class Fourier {
public:
  /**
   * @method transform
   * @param {*Image} image to be transformed
   */
  static void transform(Image* target);

  /**
   * @method inverse
   * @param {*Image} inverse transformed image
   */
  static void inverse(Image* target);
};

#endif
