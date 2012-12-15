#include <stdio.h>
#include <math.h>
#include "map.h"

Real mod(Real a, Real b)
{
  int n = (int)(a/b);
  a -= n * b;
  if (a < 0)
    a += b;
  return a;
}

Color chequer(Real xfreq, Real yfreq, Color a, Color b, Vector3 t)
{
  Real sm = mod(t.x * xfreq, 1);
  Real tm = mod(t.y * yfreq, 1);

  return ((sm < .5) ? ((tm < .5)? a : b) : ((tm < .5)? b : a));
}


Color chequer_texture(ChequerInfo *c,  Vector3 t)
{
  return chequer(c->xfreq, c->yfreq,  c->fg, c->bg, t);
}
