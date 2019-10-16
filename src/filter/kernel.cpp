#include <iostream>
#include <fstream>
#include "kernel.hpp"

int checkKernelGroup(KernelType kernelType) {
  switch (kernelType) {
    case AVERAGE:
    case GAUSSIAN3:
      return 1;
    case HIGH_A:
    case HIGH_B:
    case HIGH_C:
    case HIGH_D:
    case HIGH_E:
    case HIGH_F:
      return 2;
    case GRADIENT_X:
    case GRADIENT_Y:
    case DERIV2:
    case LAPLACE:
    case LOG:
    case SOBEL_X:
    case SOBEL_Y:
    case PREWITT_X:
    case PREWITT_Y:
    case ROBERTS_1:
    case ROBERTS_2:
      return 3;
    case UNSHARP:
    case HIGHBOOST:
    case CANNY:
      return 4;
    case MEDIAN:
    case MAX:
    case MIN:
      return 0;
    default:
      return -1;
  }
}

Kernel loadKernel(std::string filename) {
  Kernel kernel;
  int kernelSize;

  std::ifstream kernelFile;
  kernelFile.open("./src/filter/kernels/" + filename + ".txt", std::ios::in | std::ios::binary);
  if (kernelFile.is_open()) {
    // retrieving file size
    kernelFile >> kernelSize;
    kernel.assign(kernelSize, std::vector<double>());
    for (int i = 0; i < kernelSize; i++) {
      kernel[i].assign(kernelSize, 0.0);
      for (int j = 0; j < kernelSize; j++) {
        kernelFile >> kernel[i][j];
      }
    }
    kernelFile.close();
  } else {
    std::cerr << "file not found" << std::endl;
  }

  return kernel;
}
