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
  GRADIENT,
  DERIV2,
  LAPLACE,
  LOG,
  SOBEL,
  PREWITT,
  ROBERTS,
  CANNY,
  UNSHARP,
  HIGHBOOST
};

int checkKernelGroup(KernelType kernelType);

#endif
