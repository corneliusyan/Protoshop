#include <iostream>

#include "image/image.hpp"
#include "image/exception.hpp"

int main() {
  try {
    Image* img = Image::load("./res/baboon24.ppm");
    img->show();
  } catch (ImageLoadException e) {
    std::cout << e.get_message() << std::endl;
  }

  return 0;
}
