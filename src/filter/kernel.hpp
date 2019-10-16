#ifndef PROTOSHOP_FILTER_KERNEL
#define PROTOSHOP_FILTER_KERNEL

#include <vector>

#define Kernel std::vector<std::vector<double> >

enum KernelType {
  AVERAGE,
  GAUSSIAN3,
  MEDIAN,
  MAX,
  MIN,
  HIGH_A,
  HIGH_B,
  HIGH_C,
  HIGH_D,
  HIGH_E,
  HIGH_F,
  GRADIENT_X,
  GRADIENT_Y,
  DERIV2,
  LAPLACE,
  LOG,
  SOBEL_X,
  SOBEL_Y,
  PREWITT_X,
  PREWITT_Y,
  ROBERTS_1,
  ROBERTS_2,
  CANNY,
  UNSHARP,
  HIGHBOOST
};

int checkKernelGroup(KernelType kernelType);
Kernel loadKernel(std::string filename);

#endif
