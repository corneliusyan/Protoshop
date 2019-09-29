#include <iostream>

#include "image/image.hpp"
#include "image/exception.hpp"
#include "adjustment/adjustment.hpp"

int main() {
  try {
    Image* img = Image::load("./res/baboon24.ppm");
    AdjustmentGrayscale::apply(img);
    img->show();
  } catch (ImageLoadException e) {
    std::cout << e.get_message() << std::endl;
  }

  return 0;
}
