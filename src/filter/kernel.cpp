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
    case CANNY:
      return 3;
    case UNSHARP:
    case HIGHBOOST:
      return 4;
    case MEDIAN:
    case MAX:
    case MIN:
      return 0;
    default:
      return -1;
  }
}
