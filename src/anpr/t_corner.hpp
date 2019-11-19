#ifndef PROTOSHOP_ANPR_TCORNER
#define PROTOSHOP_ANPR_TCORNER

#include "./t_point.hpp"

struct t_corner {
  t_point tl; // top left
  t_point tr; // top right
  t_point bl; // bottom left
  t_point br; // bottom right

  t_corner(t_point _tl, t_point _tr, t_point _br, t_point _bl) { // ordered clockwise
    tl = _tl;
    tr = _tr;
    bl = _bl;
    br = _br;
  }
};

#endif
