#include "median.hpp"

FilterMedianStrategy::FilterMedianStrategy(int size) : FilterStrategyBase() {
  this->size = size;
}

void FilterMedianStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel new_pixel(0, 0, 0, 0);
      std::vector<pixel> sum;
      int rowOffset = - (this->size / 2);
      for (int i_k = 0; i_k < (int) this->size; i_k++) {
        int colOffset = - (this->size / 2);
        for (int j_k = 0; j_k < (int) this->size; j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          sum.push_back(temp->get_pixel(i_target, j_target));
        }
      }
      target->set_pixel(i, j, sum[sum.size() / 2]);
    }
  }
  delete temp;
}
