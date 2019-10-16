#include "convolution.hpp"

FilterConvolutionStrategy::FilterConvolutionStrategy(Kernel kernel) : FilterStrategyBase() {
  this->kernel = kernel;
}

void FilterConvolutionStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel new_pixel(0, 0, 0, 0);
      int rowOffset = - (this->kernel.size() / 2);
      for (int i_k = 0; i_k < (int) this->kernel.size(); i_k++) {
        int colOffset = - (this->kernel[i_k].size() / 2);
        for (int j_k = 0; j_k < (int) this->kernel[i_k].size(); j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          new_pixel += temp->get_pixel(i_target, j_target) * this->kernel[i_k][j_k];
        }
      }
      target->set_pixel(i, j, new_pixel);
    }
  }
  delete temp;
}
