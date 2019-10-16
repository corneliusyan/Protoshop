#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "pixel.hpp"
#include "../utils/math.hpp"

pixel::pixel() {
  len = 1;
  in = new uchar[len];
  in[0] = 0;
  alpha = 1;
}

pixel::pixel(uchar p) {
  len = 1;
  in = new uchar[len];
  in[0] = p;
  alpha = 1;
}

pixel::pixel(uchar p1, uchar p2, uchar p3) {
  len = 3;
  in = new uchar[len];
  in[0] = p1;
  in[1] = p2;
  in[2] = p3;
  alpha = 1;
}

pixel::pixel(uchar p1, uchar p2, uchar p3, uchar a) : pixel(p1, p2, p3) {
  alpha = a;
}

pixel::pixel(const pixel& other) {
  len = other.len;
  in = new uchar[len];
  for (int i = 0; i < len; i++) {
    in[i] = other.in[i];
  }
  alpha = other.alpha;
}

pixel::~pixel() {
  delete[] in;
}

pixel& pixel::operator=(const pixel& other) {
  alpha = other.alpha;
  len = other.len;
  in = new uchar[len];
  for (int i = 0; i < len; i++) {
    in[i] = other.in[i];
  }
  return *this;
}

pixel& pixel::operator+(const pixel& other) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] + other.in[i], 0, 255);
  }
  return *this;
}

pixel& pixel::operator+=(const pixel& other) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] + other.in[i], 0, 255);
  }
  return *this;
}

pixel& pixel::operator+(int scalar) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] + scalar, 0, 255);
  }
  return *this;
}

pixel& pixel::operator-(const pixel& other) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] - other.in[i], 0, 255);
  }
  return *this;
}

pixel& pixel::operator-(int scalar) {
  return *this + (-scalar);
}

pixel& pixel::operator*(const pixel& other) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] * other.in[i], 0, 255);
  }
  return *this;
}

pixel& pixel::operator*(int scalar) {
  for (int i = 0; i < len; i++) {
    in[i] = clip((int) in[i] * scalar, 0, 255);
  }
  return *this;
}

pixel& pixel::operator*(double scalar) {
  for (int i = 0; i < len; i++) {
    in[i] = clip(round((int) in[i] + scalar), 0, 255);
  }
  return *this;
}

pixel& pixel::operator/(const pixel& other) {
  for (int i = 0; i < len; i++) {
    in[i] = clip(round((double) in[i] / other.in[i]), 0, 255);
  }
  return *this;
}

pixel& pixel::operator/(int scalar) {
  for (int i = 0; i < len; i++) {
    in[i] = clip(round((double) in[i] / scalar), 0, 255);
  }
  return *this;
}

pixel& pixel::operator^(double scalar) {
  for (int i = 0; i < len; i++) {
    in[i] = clip(round((double) pow(in[i], scalar)), 0, 255);
  }
  return *this;
}

pixel& pixel::operator&(const pixel& other) {
  for (int i = 0; i < len; i++)
    in[i] &= other.in[i];
  return *this;
}

pixel& pixel::operator|(const pixel& other) {
  for (int i = 0; i < len; i++)
    in[i] |= other.in[i];
  return *this;
}


pixel& pixel::operator!(void) {
  for (int i = 0; i < len; i++)
    in[i] = !in[i];
  return *this;
}

pixel operator-(int scalar, const pixel& px) {
  pixel res(px);
  for (int i = 0; i < res.len; i++) {
    res.in[i] = clip((int) scalar - px.in[i], 0, 255);
  }
  return res;
}

bool pixel::operator<(const pixel& px) {
  return this->magnitude() < px.magnitude();
}

bool pixel::operator>(const pixel& px) {
  return this->magnitude() > px.magnitude();
}

int pixel::magnitude() const {
  int res = 0;
  for (int i = 0; i < len; i++) {
    res += in[i] * in[i];
  }
  return res / len;
}
