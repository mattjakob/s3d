#include <stdio.h>
#include <math.h>
#include "map.h"


Color image_texture(Image *i, Vector3 t)
{
  Color c00, c01, c10, c11, c;
  Real ru, rv, tu, tv;
  int u, v;

  ru = t.x * i->w;
  rv = (1 - t.y) * i->h;
  u = floor(ru); tu = ru - u;
  v = floor(rv); tv = rv - v;
  c00 = img_getc(i, u, v);
  c01 = img_getc(i, u, v+1);
  c10 = img_getc(i, u+1, v);
  c11 = img_getc(i, u+1, v+1);
  c = v3_bilerp(tu, tv, c00, c01, tv, c10, c11);
  return c_scale(1./255.,c);
}





