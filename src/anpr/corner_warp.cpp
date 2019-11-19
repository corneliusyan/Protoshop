#include "../image/image.hpp"
#include "./t_corner.hpp"
#include "./corner_warp.hpp"
#include <cmath>
#include <algorithm>


Image* warpByCorner(Image* image_src, t_corner src) {
  int widthA, widthB, maxWidth, heightA, heightB, maxHeight;
  widthA = round(sqrt(((corner.br.r - corner.bl.r) ^ 2) + ((corner.br.c - corner.bl.c) ^ 2)));
  widthA = round(sqrt(((corner.tr.r - corner.tl.r) ^ 2) + ((corner.tr.c - corner.tl.c) ^ 2)));
  maxWidth = std::max(widthA,widthB);

  heightA = round(sqrt(((corner.tr.r - corner.br.r) ^ 2) + ((corner.tr.c - corner.br.c) ^ 2)));
  heightB = round(sqrt(((corner.tl.r - corner.bl.r) ^ 2) + ((corner.tl.c - corner.bl.c) ^ 2)));
  maxHeight = std::max(heightA,heightB);

  Image* img = new Image(image_src->imageType, maxHeight, maxWidth);
  int N = img->height, M = img->width;

  t_point tl(0,0), tr(maxWidth-1, 0), br(maxWidth-1, maxHeight-1), bl(0, maxHeight-1);
  t_corner dst(tl,tr,br,bl);

  /*
  Todo:
  1. getPerspectiveTransform
  2. Solve Matrix
  3. warpPerspective -> kali aja
  4. Handle non integer
  5. Convert to binary
  */


  return NULL;
}
