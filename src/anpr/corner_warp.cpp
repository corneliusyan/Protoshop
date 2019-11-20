#include "../image/image.hpp"
#include "./t_corner.hpp"
#include "./corner_warp.hpp"
#include <cmath>
#include <algorithm>

Point* tcornerToPoint(t_corner _src) {
  Point* src = new Point[4];
  src[0].x = _src.tl.c; src[0].y = _src.tl.r;
  src[1].x = _src.tr.c; src[1].y = _src.tr.r;
  src[2].x = _src.br.c; src[2].y = _src.br.r;
  src[3].x = _src.bl.c; src[3].y = _src.bl.r;
  return src;
}

Image* warpByCorner(Image* image_src, t_corner _src) {
  int widthA, widthB, maxWidth, heightA, heightB, maxHeight;
  // Get max width and height
  widthA = round(sqrt(((_src.br.r - _src.bl.r) ^ 2) + ((_src.br.c - _src.bl.c) ^ 2)));
  widthA = round(sqrt(((_src.tr.r - _src.tl.r) ^ 2) + ((_src.tr.c - _src.tl.c) ^ 2)));
  maxWidth = std::max(widthA,widthB);
  heightA = round(sqrt(((_src.tr.r - _src.br.r) ^ 2) + ((_src.tr.c - _src.br.c) ^ 2)));
  heightB = round(sqrt(((_src.tl.r - _src.bl.r) ^ 2) + ((_src.tl.c - _src.bl.c) ^ 2)));
  maxHeight = std::max(heightA,heightB);

  Image* img = new Image(image_src->imageType, maxHeight, maxWidth);

  t_point tl(0,0), tr(maxWidth-1, 0), br(maxWidth-1, maxHeight-1), bl(0, maxHeight-1);
  t_corner _dst(tl,tr,br,bl);

  double M[3][3], X[8];
  double a[8][8], b[8];
  Point *src,*dst;
  src = tcornerToPoint(_src);
  dst = tcornerToPoint(_dst);
  for( int i = 0; i < 4; ++i )
    {
        a[i][0] = a[i+4][3] = src[i].x;
        a[i][1] = a[i+4][4] = src[i].y;
        a[i][2] = a[i+4][5] = 1;
        a[i][3] = a[i][4] = a[i][5] =
        a[i+4][0] = a[i+4][1] = a[i+4][2] = 0;
        a[i][6] = -src[i].x*dst[i].x;
        a[i][7] = -src[i].y*dst[i].x;
        a[i+4][6] = -src[i].x*dst[i].y;
        a[i+4][7] = -src[i].y*dst[i].y;
        b[i] = dst[i].x;
        b[i+4] = dst[i].y;
    }

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
