#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdlib>
#include <cstdarg>
#define uchar unsigned char

struct pixel {
  unsigned char len;
  unsigned char alpha;
  unsigned char* in;

  pixel();
  pixel(uchar p);
  pixel(uchar p1, uchar p2, uchar p3);
  pixel(uchar p1, uchar p2, uchar p3, uchar a);
  pixel(const pixel& other);

  ~pixel();

  pixel& operator=(const pixel& other);
  pixel& operator+(int scalar);
  pixel& operator-(int scalar);
};

pixel operator-(int scalar, const pixel& px);

#endif
