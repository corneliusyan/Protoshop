#include "filter.hpp"
#include "kernel.hpp"
#include "strategy/strategy.hpp"

Filter::Filter(KernelType kernelType) {
  this->strategy = NULL;
  int group = checkKernelGroup(kernelType);

  /** Convolutional kernel **/
  if (0 < group && group < 4) {
    std::string filename;

    if (kernelType == AVERAGE) { filename = "average"; }
    else if (kernelType == GAUSSIAN3) { filename = "gaussian3"; }
    else if (kernelType == HIGH_A) { filename = "highA"; }
    else if (kernelType == HIGH_B) { filename = "highB"; }
    else if (kernelType == HIGH_C) { filename = "highC"; }
    else if (kernelType == HIGH_D) { filename = "highD"; }
    else if (kernelType == HIGH_E) { filename = "highE"; }
    else if (kernelType == HIGH_F) { filename = "highF"; }
    else if (kernelType == GRADIENT_X) { filename = "gradientX"; }
    else if (kernelType == GRADIENT_Y) { filename = "gradientY"; }
    else if (kernelType == DERIV2) { filename = "deriv2"; }
    else if (kernelType == LAPLACE) { filename = "laplace"; }
    else if (kernelType == LOG) { filename = "log"; }
    else if (kernelType == SOBEL_X) { filename = "sobelX"; }
    else if (kernelType == SOBEL_Y) { filename = "sobelY"; }
    else if (kernelType == PREWITT_X) { filename = "prewittX"; }
    else if (kernelType == PREWITT_Y) { filename = "prewittY"; }
    else if (kernelType == ROBERTS_1) { filename = "roberts1"; }
    else if (kernelType == ROBERTS_2) { filename = "roberts2"; }

    Kernel kernel = loadKernel(filename);
    this->strategy = new FilterConvolutionStrategy(kernel);
  }

  /** Non linear kernel **/
  else if (group == 0) {
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

  /** Complex kernel **/
  else if (group == 4) {
    switch(kernelType) {
      case UNSHARP:
        this->strategy = new FilterUnsharpStrategy();
        break;
      case HIGHBOOST:
        this->strategy = new FilterHighboostStrategy(2.4);
        break;
      case CANNY:
        this->strategy = new FilterCannyStrategy();
        break;
    }
  }
}

void Filter::apply(Image* target) {
  if (this->strategy != NULL) {
    this->strategy->apply(target);
  } else {
    std::cerr << "NULL Strategy" << std::endl;
  }
}
