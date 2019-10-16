#include "complex.hpp"
#include "convolution.hpp"
#include "../../utils/math.hpp"

void FilterUnsharpStrategy::apply(Image* target) {
  Kernel averageKernel;
  averageKernel.assign(5, std::vector<double>());
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      averageKernel[i].push_back(0.04);
    }
  }

  Image* lowPass = new Image(*target);
  FilterConvolutionStrategy* lowpassStrategy = new FilterConvolutionStrategy(averageKernel);
  lowpassStrategy->apply(lowPass);

  Image* highPass = new Image(*target);
  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      highPass->set_pixel(i, j, target->get_pixel(i, j) - lowPass->get_pixel(i, j));
    }
  }

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      target->set_pixel(i, j, target->get_pixel(i, j) + highPass->get_pixel(i, j));
    }
  }

  delete lowPass;
  delete highPass;
}

FilterHighboostStrategy::FilterHighboostStrategy(double alpha) : FilterStrategyBase() {
  this->alpha = alpha;
}

void FilterHighboostStrategy::apply(Image* target) {
  Kernel averageKernel;
  averageKernel.assign(5, std::vector<double>());
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      averageKernel[i].push_back(0.04);
    }
  }

  Image* lowPass = new Image(*target);
  FilterConvolutionStrategy* lowpassStrategy = new FilterConvolutionStrategy(averageKernel);
  lowpassStrategy->apply(lowPass);

  for (int i = 0; i < target->height; i++) {
    for (int j = 0; j < target->width; j++) {
      std::vector<int> tempPixel;
      pixel targetPixel = target->get_pixel(i, j);
      pixel lowpassPixel = lowPass->get_pixel(i, j);
      for (int k = 0; k < targetPixel.len; k++) {
        tempPixel.push_back(
          clip((double) targetPixel.in[k] * this->alpha - lowpassPixel.in[k], 0, 255)
        );
      }
      pixel resultPixel;
      if (tempPixel.size() == 3) {
        resultPixel = pixel(tempPixel[0], tempPixel[2], tempPixel[2]);
      } else if (tempPixel.size() == 1) {
        resultPixel = pixel(tempPixel[0]);
      } else {
        std::cerr << "unknown pixel" << std::endl;
      }
      target->set_pixel(i, j, resultPixel);
    }
  }

  delete lowPass;
}
