#include "filter.hpp"
#include "kernel.hpp"
#include "strategy/strategy.hpp"

Filter::Filter(KernelType kernelType) {
  /** Convolutional kernel **/
  if (kernelTypeHLN(kernelType) < 3) {
    Kernel kernel;
    int kernelSize;
    double _kernel[10][10];  // WARN: hardcoded kernel size of 19

    if (kernelType == AVERAGE) {
      kernelSize = 3;
      _kernel[0][0] = 1.0 / 9; _kernel[0][1] = 1.0 / 9; _kernel[0][2] = 1.0 / 9;
      _kernel[1][0] = 1.0 / 9; _kernel[1][1] = 1.0 / 9; _kernel[1][2] = 1.0 / 9;
      _kernel[2][0] = 1.0 / 9; _kernel[2][1] = 1.0 / 9; _kernel[2][2] = 1.0 / 9;
    } else if (kernelType == GAUSSIAN3) {
      kernelSize = 3;
      _kernel[0][0] = 1.0 / 16; _kernel[0][1] = 2.0 / 16; _kernel[0][2] = 1.0 / 16;
      _kernel[1][0] = 2.0 / 16; _kernel[1][1] = 4.0 / 16; _kernel[1][2] = 2.0 / 16;
      _kernel[2][0] = 1.0 / 16; _kernel[2][1] = 2.0 / 16; _kernel[2][2] = 1.0 / 16;
    } else if (kernelType == HIGH_A) {
      kernelSize = 3;
      _kernel[0][0] = -1; _kernel[0][1] = -1; _kernel[0][2] = -1;
      _kernel[1][0] = -1; _kernel[1][1] =  8; _kernel[1][2] = -1;
      _kernel[2][0] = -1; _kernel[2][1] = -1; _kernel[2][2] = -1;
    } else if (kernelType == HIGH_B) {
      kernelSize = 3;
      _kernel[0][0] = -1; _kernel[0][1] = -1; _kernel[0][2] = -1;
      _kernel[1][0] = -1; _kernel[1][1] =  9; _kernel[1][2] = -1;
      _kernel[2][0] = -1; _kernel[2][1] = -1; _kernel[2][2] = -1;
    } else if (kernelType == HIGH_C) {
      kernelSize = 3;
      _kernel[0][0] =  0; _kernel[0][1] = -1; _kernel[0][2] =  0;
      _kernel[1][0] = -1; _kernel[1][1] =  5; _kernel[1][2] = -1;
      _kernel[2][0] =  0; _kernel[2][1] = -1; _kernel[2][2] =  0;
    } else if (kernelType == HIGH_D) {
      kernelSize = 3;
      _kernel[0][0] =  1; _kernel[0][1] = -2; _kernel[0][2] =  1;
      _kernel[1][0] = -2; _kernel[1][1] =  5; _kernel[1][2] = -2;
      _kernel[2][0] =  1; _kernel[2][1] = -2; _kernel[2][2] =  1;
    } else if (kernelType == HIGH_E) {
      kernelSize = 3;
      _kernel[0][0] =  1; _kernel[0][1] = -2; _kernel[0][2] =  1;
      _kernel[1][0] = -2; _kernel[1][1] =  4; _kernel[1][2] = -2;
      _kernel[2][0] =  1; _kernel[2][1] = -2; _kernel[2][2] =  1;
    } else if (kernelType == HIGH_F) {
      kernelSize = 3;
      _kernel[0][0] =  0; _kernel[0][1] =  1; _kernel[0][2] =  0;
      _kernel[1][0] =  1; _kernel[1][1] = -4; _kernel[1][2] =  1;
      _kernel[2][0] =  0; _kernel[2][1] =  1; _kernel[2][2] =  0;
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
  else if (kernelTypeHLN(kernelType) == 3) {
    switch (kernelType) {
      case MEDIAN:
        this->strategy = new FilterMedianStrategy(3);
        break;
      case MAX:
        this->strategy = new FilterMaxStrategy(3);
        break;
      case MIN:
        this->strategy = new FilterMinStrategy(3);
        break;
    }
  }
}

void Filter::apply(Image* target) {
  this->strategy->apply(target);
}
