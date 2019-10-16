#include "filter.hpp"
#include "kernel.hpp"

Filter::Filter(KernelType kernelType) {
  if (kernelType == GAUSSIAN3) {
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
    this->strategy = new FilterConvolutionStrategy(kernel);
  }
}

void Filter::apply(Image* target) {
  this->strategy->apply(target);
}
