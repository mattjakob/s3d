#include "hpoly.h"


Hpoly *hpoly_alloc(int n)
{
  Hpoly *p = NEWSTRUCT(Hpoly);
  p->n = n;
  p->v = NEWARRAY(n, Vector4);
  return p;
}

Hpoly *hpoly_polyxform(Hpoly *d, Poly *s, Matrix4 m)
{
  int i;
  for (i = 0; i < d->n; i++) {
    d->v[i] = v4_m4mult(v4_v3conv(s->v[i]), m);
    d->v[i].x /= d->v[i].w;
    d->v[i].y /= d->v[i].w;
    d->v[i].z /= d->v[i].w;
  }
  return d;
}

int hpoly_copy(Hpoly *d, Hpoly *s)
{
  int i;
  for (i = 0; i < s->n; i++)
    d->v[i] = s->v[i];
  return (d->n = s->n);
}
