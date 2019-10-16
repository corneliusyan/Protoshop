#ifndef PROTOSHOP_FILTER_KERNEL
#define PROTOSHOP_FILTER_KERNEL

#include <vector>

#define Kernel std::vector<std::vector<double> >

enum KernelType {
  GAUSSIAN3,
  MEDIAN
};

#endif
