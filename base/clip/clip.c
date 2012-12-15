#include <stdio.h>
#include <math.h>
#include "defs.h"
#include "geom.h"
#include "poly.h"

#define LFT 0
#define RGT 1
#define TOP 2
#define BOT 3
#define BAK 4
#define FRT 5

#define MAXV 16
#define MAXD ((MAXV+1)*(FRT+1))


static Real plane_point_dist(int plane, Vector3 v, Real h)
{
  switch (plane) {
  case LFT: return v.z + v.x;
  case RGT: return v.z - v.x;
  case TOP: return v.z + v.y;
  case BOT: return v.z - v.y;
  case BAK: return 1.0 - v.z;
  case FRT: return -h + v.z;
  }
}


#define DA(dd, i, p) dd[(p*MAXV)+i]

#define PLANE_CROSS(D0, D1) ((D0) * (D1) < 0.0)
#define ON_POSITIVE_SIDE(D1) ((D1) >= 0.0)

int pclip_store(int plane, Poly *s, Poly *d, Real h, double *dd)
{
  int i, k0, k1;
  double d0, d1;

  for (d->n = k1 = i = 0; i <= s->n ; i++,  k1 = (i == s->n)? 0 : i) {
    d1 = plane_point_dist(plane, s->v[k1], h);
    DA(dd, i, plane) = d1;
    if (i != 0) {
      if (PLANE_CROSS(d0, d1))
	d->v[d->n++] = v3_add(s->v[k1], v3_scale(d1/(d1-d0), v3_sub(s->v[k0], s->v[k1])));
      if (ON_POSITIVE_SIDE(d1))
	d->v[d->n++] = s->v[k1];
    }
    d0 = d1;
    k0 = k1;
  }
  return (plane++ == FRT)? d->n : pclip_store(plane, d, s, h, dd);
}

int pclip_apply(int plane, Poly *s, Poly *d, Real h, double *dd)
{
  int i, k0, k1;
  double d0, d1;

  for (d->n = k1 = i = 0; i <= s->n ; i++,  k1 = (i == s->n)? 0 : i) {
    d1 = DA(dd, i, plane);
    if (i != 0) {
      if (PLANE_CROSS(d0, d1))
	d->v[d->n++] = v3_add(s->v[k1], v3_scale(d1/(d1-d0), v3_sub(s->v[k0], s->v[k1])));
      if (ON_POSITIVE_SIDE(d1))
	d->v[d->n++] = s->v[k1];
    }
    d0 = d1;
    k0 = k1;
  }
  return (plane++ == FRT)? d->n : pclip_apply(plane, d, s, h, dd);
}

int clip_copy(int (*clip_do)(), Poly *p, Real h, void (*dispose)(), double *dd)
{
  Vector3 vs[MAXV], vd[MAXV];
  Poly s = {NULL, 0, vs}, d = {NULL, 0, vd};

  poly_copy(p, &s);
  if (clip_do(0, &s, &d, h, dd) > p->n) {
    if (dispose != NULL)
      dispose(p->v);
    p->v = NEWARRAY(s.n, Vector3);
  }
  poly_copy(&s, p);
  return s.n;
}


int poly_clip(Real h, Poly *p, void (*dispose)(), int chain)
{
  double dd[MAXD];
  Poly *a;
  int n; 

  if (p->n > MAXV)
    error("(poly clip) too many vertices");

  n = clip_copy(pclip_store, p, h, dispose, dd);
  if (!chain)
    return n;
  for (a = p->next; a != NULL; a = a->next) 
    n = clip_copy(pclip_apply, a, h, dispose, dd);

  return n;
}
