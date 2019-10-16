#ifndef ENHANCEMENT_H
#define ENHANCEMENT_H

#include "base.hpp"

class AdjustmentEnhancement : public Adjustment {
public:
  static void brighten(Image* target, double multiplier);
  static void contrastStretch(Image* target, int rMin, int rMax);
  static void logTransform(Image* target, double c);
  static void inverseLog(Image* target, double c);
  static void power(Image* target, double c);
  static void graySlicing(Image* target, int rMin, int rMax);
  static void bitSlicing(Image* target);
};

#endif // ENHANCEMENT_H

// brighten, constrastStretch, log, inverseLog, power, graySlicing, bitSlicing
