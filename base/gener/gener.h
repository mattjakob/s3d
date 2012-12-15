#ifndef GENER_H
#define GENER_H

#include "defs.h"
#include "geom.h"
#include "poly.h"


#define G_TX  1
#define G_TY  2
#define G_TZ  3
#define G_RX  4
#define G_RY  5
#define G_RZ  6
#define G_SX  7
#define G_SY  8
#define G_SZ  9

Poly *rotsurf(int n, Vector3 *g, int m);
Poly *gener_affine(int n, Vector3 *g, int m, Matrix4 *h);
Matrix4 m4_compxform(int k,  char *t, Real **h, int j);
Matrix4 *affine_group(int l, int m, char *t, Real **p);

Real *linear(Real v0, Real v1, int n);

#endif
