#include "nonlinear.hpp"

FilterMedianStrategy::FilterMedianStrategy(int size) : FilterStrategyBase() {
  this->size = size;
}

void FilterMedianStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      std::vector<pixel> pixels;
      int rowOffset = - (this->size / 2);
      for (int i_k = 0; i_k < (int) this->size; i_k++) {
        int colOffset = - (this->size / 2);
        for (int j_k = 0; j_k < (int) this->size; j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          pixels.push_back(temp->get_pixel(i_target, j_target));
        }
      }
      target->set_pixel(i, j, pixels[pixels.size() / 2]);
    }
  }
  delete temp;
}


FilterMaxStrategy::FilterMaxStrategy(int size) : FilterStrategyBase() {
  this->size = size;
}

void FilterMaxStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel new_pixel(0, 0, 0, 0);
      int rowOffset = - (this->size / 2);
      for (int i_k = 0; i_k < (int) this->size; i_k++) {
        int colOffset = - (this->size / 2);
        for (int j_k = 0; j_k < (int) this->size; j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          pixel prev = temp->get_pixel(i_target, j_target);
          if (prev > new_pixel) {
            new_pixel = prev;
          }
        }
      }
      target->set_pixel(i, j, new_pixel);
    }
  }
  delete temp;
}


FilterMinStrategy::FilterMinStrategy(int size) : FilterStrategyBase() {
  this->size = size;
}

void FilterMinStrategy::apply(Image* target) {
  Image* temp = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      pixel new_pixel(255, 255, 255, 0);
      int rowOffset = - (this->size / 2);
      for (int i_k = 0; i_k < (int) this->size; i_k++) {
        int colOffset = - (this->size / 2);
        for (int j_k = 0; j_k < (int) this->size; j_k++) {
          int i_target = std::max(0, std::min(target->height - 1, i + rowOffset + i_k));
          int j_target = std::max(0, std::min(target->width - 1, j + colOffset + j_k));
          pixel prev = temp->get_pixel(i_target, j_target);
          if (prev < new_pixel) {
            new_pixel = prev;
          }
        }
      }
      target->set_pixel(i, j, new_pixel);
    }
  }
  delete temp;
}
