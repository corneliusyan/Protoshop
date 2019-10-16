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
    case MEDIAN:
    case MAX:
    case MIN:
      return 3;
    default:
      return 0;
  }
}
