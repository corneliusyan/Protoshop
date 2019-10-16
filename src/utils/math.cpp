#include "math.hpp"

int clip(int val, int lo, int hi) {
  if (val < lo) return lo;
  if (val > hi) return hi;
  return val;
}
