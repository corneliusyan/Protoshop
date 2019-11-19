#ifndef PROTOSHOP_ANPR_AUTO_THRESHOLD
#define PROTOSHOP_ANPR_AUTO_THRESHOLD

#include "../image/image.hpp"

BWImage* autoThreshold(Image* image);
// create new image, thresholded automatically
// without ever changing the original image

#endif
