#include <vector>
#include <cmath>
#include "convolution.hpp"
#include "../../utils/math.hpp"

FilterConvolutionStrategy::FilterConvolutionStrategy(Kernel kernel) : FilterStrategyBase() {
  this->kernel = kernel;
}

void FilterConvolutionStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      std::vector<double> new_pixel;
      for (int k = 0; k < temp->get_pixel(0, 0).len; k++) { new_pixel.push_back(0); 
}
      int rowOffset = - (this->kernel.size() / 2);
      for (int i_k = 0; i_k < (int) this->kernel.size(); i_k++) {
        int colOffset = - (this->kernel[i_k].size() / 2);
        for (int j_k = 0; j_k < (int) this->kernel[i_k].size(); j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));

          pixel px = temp->get_pixel(i_target, j_target);
          for (int k = 0; k < px.len; k++) {
            new_pixel[k] += px.in[k] * this->kernel[i_k][j_k];
          }
        }
      }
      pixel res;
      if (new_pixel.size() == 3) {
        res = pixel(
          (uchar) clip(round(new_pixel[0]), 0, 255),
          (uchar) clip(round(new_pixel[1]), 0, 255),
          (uchar) clip(round(new_pixel[2]), 0, 255)
        );
      } else if (new_pixel.size() == 1) {
        res = pixel(
          (uchar) clip(round(new_pixel[0]), 0, 255)
        );
      }
      target->set_pixel(i, j, res);
    }
  }
  delete temp;
}
