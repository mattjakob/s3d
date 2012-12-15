#include <stdio.h>
#include "raster.h"
#include "map.h"

void *texture_set(TextureData *d,
		  Poly *w, Poly *t, Poly *p, Poly *n, Poly *u, Poly *v,
		  RContext *rc, Material *m)
{
  d->vpar[TEX_W] = w;
  d->vpar[TEX_T] = t;
  d->vpar[TEX_P] = p;
  d->vpar[TEX_N] = n;
  d->vpar[TEX_U] = u;
  d->vpar[TEX_V] = v;
  d->rc = rc;
  d->rc->m = m;
  return (void *)d;
}

#define TEX_E TEX_MAXPAR

void texture_shadepaint(Vector3 p, int n, int lv, Real lt, int rv, Real rt, Real st, void *data)
{
  Vector3 a[TEX_MAXPAR+1];
  Color c; int i; 
  TextureData *d = data;

  a[TEX_W] = seg_bilerp(d->vpar[TEX_W], n, st, lv, lt, rv, rt);
  for (i = 1; i <TEX_MAXPAR ; i++)
    a[i] = v3_scale(1/a[TEX_W].z, seg_bilerp(d->vpar[i], n, st, lv, lt, rv, rt));
  a[TEX_N] = v3_unit(a[TEX_N]);
  a[TEX_E] = v3_unit(v3_sub(d->rc->c->center, a[TEX_P]));
  c = (*d->rc->m->luminance)(rc_tset(d->rc, a[TEX_E], a[TEX_P], a[TEX_N],
				     a[TEX_T], a[TEX_U] ,a[TEX_V], d->rc->m));
  img_putc(d->rc->img, p.x, p.y, col_dpymap(c));
}


Poly *texture_wscale(Poly *w, Poly *p)
{
  Poly *l; int i;
  for (i = 0; i < w->n; i++) 
    for (l = p; l != NULL; l = l->next)
      l->v[i] = v3_scale(w->v[i].z, l->v[i]);
  return w;
}


Poly  *poly_wz_hpoly(Poly *q, Poly *w, Hpoly *s)
{
  int i;
  for (i = 0; i < s->n; i++) {
    Real rw = 1./s->v[i].w;
    w->v[i] = v3_make(rw, rw, rw);
    q->v[i] = v3_make(s->v[i].x, s->v[i].y, s->v[i].z);
  }
  return q;
}
