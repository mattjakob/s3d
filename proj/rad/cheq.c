#include <stdio.h>
#include "geom.h"
#include "poly.h"

extern Poly *plist_refine(Poly *p, Real s, int maxrec);

int main(int argc, char **argv)
{
  int i;
  Real x0, x1, y0, y1, z0, z1;
  Vector3 v1, v2, v3, v4, v5, v6, v7, v8;
  Poly *quad[2], *plist = NULL;

  x0 = -5;  x1 = 5;
  y0 = -2;  y1 = 2;
  z0 = -5;  z1 = 5;

  v1 = v3_make(x0, y0, z0);
  v2 = v3_make(x1, y0, z0);
  v3 = v3_make(x1, y0, z1);
  v4 = v3_make(x0, y0, z1);

  quad[0] = poly3_make(v2, v1, v3);
  quad[1] = poly3_make(v3, v1, v4);

  for (i = 0; i < 2; i++)
    plist = poly_insert(plist, quad[i]);

  plist = plist_refine(plist, 0.0, 1);
    
  trilist_write(plist, stdout);

  exit(1);
}



