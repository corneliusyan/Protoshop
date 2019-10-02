#include <iostream>

#include "image/image.hpp"
#include "image/exception.hpp"
#include "adjustment/adjustment.hpp"

int main() {
  try {
    // Image* img_lena = Image::load("./res/lena.bmp");
    // Image* img_baboon = Image::load("./res/lena.bmp");
    // Image* img = *img_lena + *img_baboon;
    // img->show();
    Image* img = Image::load("./res/lena.bmp");
    AdjustmentTranslate::apply(img, 30, 25);
    img->show();
    // Image* img2 = *img + *img;
    // img2->show();
  } catch (ImageLoadException e) {
    std::cout << e.get_message() << std::endl;
  }

  return 0;
}
