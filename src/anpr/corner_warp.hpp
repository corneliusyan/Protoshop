#ifndef PROTOSHOP_ANPR_CORNER_WRAP
#define PROTOSHOP_ANPR_CORNER_WRAP

#include "../image/image.hpp"
#include "./t_corner.hpp"

Image* warpByCorner(Image* img, t_corner corner);
// create a new image by wrapping with corner as new corner

#endif
