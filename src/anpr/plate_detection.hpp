#ifndef PROTOSHOP_ANPR_PLATE_DETECTION
#define PROTOSHOP_ANPR_PLATE_DETECTION

#include "../image/image.hpp"
#include "./t_corner.hpp"

t_corner plateDetection(Image* img);
// detect a plate and return the corner of plate's corner
// without changing the image

#endif
