#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdlib>
#include <cstdarg>
#define uchar unsigned char

struct pixel {
  unsigned char len;
  unsigned char alpha;
  unsigned char* in;

  pixel(uchar p) {
    len = 1;
    in = (uchar*) malloc(len * sizeof (uchar));
    in[0] = p;
    alpha = 1;
  }

  pixel(uchar p1, uchar p2, uchar p3) {
    len = 3;
    in = (uchar*) malloc(len * sizeof (uchar));
    in[0] = p1;
    in[1] = p2;
    in[2] = p3;
    alpha = 1;
  }

  pixel(uchar p1, uchar p2, uchar p3, uchar a) : pixel(p1, p2, p3) {
    alpha = a;
  }

  ~pixel() {
    delete in;
  }

  void operator=(const pixel& other) {
    alpha = other.alpha;
    for (int i = 0; i < len; i++) {
      in[i] = other.in[i];
    }
  }
};

#endif
