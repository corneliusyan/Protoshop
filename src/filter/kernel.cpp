#include "kernel.hpp"

int kernelTypeHLN(KernelType kernelType) {
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
    case GRADIENT:
    case DERIV2:
    case LAPLACE:
    case LOG:
    case SOBEL:
    case PREWITT:
    case ROBERTS:
    case CANNY:
      return 3;
    case MEDIAN:
    case MAX:
    case MIN:
      return 0;
    default:
      return -1;
  }
}
