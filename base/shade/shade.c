#include <stdio.h>
#include "shade.h"
#include "raster.h"


Color point_shade(Vector3 p, Vector3 n, Vector3 v, RContext *rc, Material *m)
{
  return (*m->luminance)(rc_set(rc, v3_unit(v3_sub(v, p)), p, n, m));
}

Color flat_shade(Poly *p, Vector3 v, RContext *rc, Material *m)
{
  Vector3 c = poly_centr(p);
  Vector3 n = poly_normal(p);
  return (*m->luminance)(rc_set(rc, v3_unit(v3_sub(v, c)), c, n, m));
}


void *gouraud_set(GouraudData *g, Poly *c, Image *i)
{
  g->img = i;
  g->cols = c;
  return (void *)g;
}

void gouraud_shade(Poly *c, Poly *p, Poly *n, Vector3 v, RContext *rc, Material *m)
{
  int i;
  for (i = 0; i < p->n; i++)
    c->v[i] = (*m->luminance)(rc_set(rc, v3_unit(v3_sub(v, p->v[i])), p->v[i], n->v[i], m));
}

void gouraud_paint(Vector3 p, int n, int lv, Real lt, int rv, Real rt, Real st,void *data)
{
  GouraudData *d = data;
  Vector3 c = seg_bilerp(d->cols, n, st, lv, lt, rv, rt);
  img_putc(d->img, p.x, p.y, col_dpymap(c));
}

void *phong_set(PhongData *d, Poly *p, Poly *n, Vector3 v, RContext *rc, Material *m)
{
  d->pnts = p;
  d->norms = n;
  d->v = v;
  d->rc = rc;
  d->rc->m = m;
  return (void *)d;
}

void phong_shadepaint(Vector3 p, int n, int lv, Real lt, int rv, Real rt, Real st, void *data)
{
  PhongData *d = data;
  Vector3 pv = seg_bilerp(d->pnts, n, st, lv, lt, rv, rt);
  Vector3 pn = v3_unit(seg_bilerp(d->norms, n, st, lv, lt, rv, rt));
  Color c = point_shade(pv, pn, d->v, d->rc, d->rc->m);
  img_putc(d->rc->img, p.x, p.y, col_dpymap(c));
}
