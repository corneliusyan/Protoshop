#include <vector>
#include <algorithm>
#include "linear.hpp"

void FilterLinear::apply(Image* target) {
  Image* temp = new Image(*target);
  Kernel kernel = this->getKernel();
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel new_pixel(0, 0, 0, 0);
      int rowOffset = - (kernel.size() / 2);
      for (int i_k = 0; i_k < (int) kernel.size(); i_k++) {
        int colOffset = - (kernel[i_k].size() / 2);
        for (int j_k = 0; j_k < (int) kernel[i_k].size(); j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          new_pixel += temp->get_pixel(i_target, j_target) * kernel[i_k][j_k];
        }
      }
      target->set_pixel(i, j, new_pixel);
    }
  }
  delete temp;
}

Kernel FilterGaussian::getKernel() {
  Kernel kernel;
  const int kernelSize = 3;
  const double _kernel[kernelSize][kernelSize] = {
    {1.0 / 16, 2.0 / 16, 1.0 / 16},
    {2.0 / 16, 4.0 / 16, 2.0 / 16},
    {1.0 / 16, 2.0 / 16, 1.0 / 16}
  };
  kernel.assign(kernelSize, std::vector<double>());
  for (int i = 0; i < kernelSize; i++) {
    kernel[i].assign(kernelSize, 0.0);
    for (int j = 0; j < kernelSize; j++) {
      kernel[i][j] = _kernel[i][j];
    }
  }
  return kernel;
}
