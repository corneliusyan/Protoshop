#ifndef PROTOSHOP_ANPR_TPOINT
#define PROTOSHOP_ANPR_TPOINT

struct t_point {
  // use (r, c) instead of (x, y) because the image is actually a matrix
  // that use r and c as index
  int r;
  int c;

  t_point(int _r, int _c) {
    r = _r;
    c = _c;
  }
};

#endif
