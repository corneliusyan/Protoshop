#include "filter.hpp"
#include "kernel.hpp"
#include "strategy/strategy.hpp"

Filter::Filter(KernelType kernelType) {
  /** Convolutional kernel **/
  if (kernelType == GAUSSIAN3) {
    Kernel kernel;
    int kernelSize;
    double _kernel[10][10];  // WARN: hardcoded kernel size of 19

    if (kernelType == GAUSSIAN3) {
      kernelSize = 3;
      _kernel[0][0] = 1.0 / 16; _kernel[0][1] = 2.0 / 16; _kernel[0][2] = 1.0 / 16;
      _kernel[1][0] = 2.0 / 16; _kernel[1][1] = 4.0 / 16; _kernel[1][2] = 2.0 / 16;
      _kernel[2][0] = 1.0 / 16; _kernel[2][1] = 2.0 / 16; _kernel[2][2] = 1.0 / 16;
    }

    kernel.assign(kernelSize, std::vector<double>());
    for (int i = 0; i < kernelSize; i++) {
      kernel[i].assign(kernelSize, 0.0);
      for (int j = 0; j < kernelSize; j++) {
        kernel[i][j] = _kernel[i][j];
      }
    }
    this->strategy = new FilterConvolutionStrategy(kernel);
  }

  /** Non linear kernel **/
  else if (kernelType == MEDIAN) {
    switch (kernelType) {
      case MEDIAN:
        this->strategy = new FilterMedianStrategy(3);
        break;
    }
  }
}

void Filter::apply(Image* target) {
  this->strategy->apply(target);
}
