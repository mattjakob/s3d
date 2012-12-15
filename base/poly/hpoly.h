#ifndef HPOLY_H
#define HPOLY_H

#include "poly.h"

typedef struct Hpoly {
  int          n;
  Vector4     *v;
} Hpoly;


Hpoly *hpoly_alloc(int n);
int    hpoly_copy(Hpoly *d, Hpoly *s);
Hpoly *hpoly_polyxform(Hpoly *d, Poly *s, Matrix4 m);


#endif
