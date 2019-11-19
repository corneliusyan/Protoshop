#ifndef PROTOSHOP_ANPR
#define PROTOSHOP_ANPR

#include <iostream>
#include "../image/image.hpp"
#include "./auto_threshold.hpp"
#include "./corner_warp.hpp"
#include "./number_recognition.hpp"
#include "./plate_detection.hpp"
#include "./t_corner.hpp"

std::string ANPR(Image* img);

#endif
