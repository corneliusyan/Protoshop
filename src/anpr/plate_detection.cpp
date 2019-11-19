#include "../image/image.hpp"
#include "./plate_detection.hpp"
#include "./t_corner.hpp"

t_corner plateDetection(Image* img) {
  // stub
  return t_corner(
    t_point(0, 0),
    t_point(0, img->width),
    t_point(img->height, img->width),
    t_point(img->height, 0)
  );
}
