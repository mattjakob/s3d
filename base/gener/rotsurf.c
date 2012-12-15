#include <stdio.h>
#include "poly.h"
#include "gener.h"


Real *linear(Real v0, Real v1, int n)
{
  int i;
  Real *x = NEWTARRAY(n, Real);
  Real incr = (v1 - v0) / (n -1);

  for (i = 0; i < n; i++)
    x[i] = v0 + (incr * i);

  return x;
}


Poly *rotsurf(int n, Vector3 *g, int m)
{
  Matrix4 *h; Real *p[1]; Poly *s;
  char t[1] = {G_RY};

  p[0] = linear(0, PITIMES2, m);
  s = gener_affine(n, g, m, h = affine_group(1, m, t, p));
  efree(h);
  return s;
}


