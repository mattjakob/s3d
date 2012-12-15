#include "raster.h"
#include "scan_obj.h"

#define SNAP_XY(V) {V.x = rint(V.x), V.y = rint(V.y);}

#define PREV(K,N) ((K == N)? 0 : ((K == 0)? N - 1 : N))
#define NEXT(K,N) ((K == 0)? N : ((K == N)? N - 1 : 0))


void scan_poly(Poly *p, Paint *pfun, void *pdata)
{
  int k;
  for (k = 2; k < p->n; k++)
    scan_spoly3(p, k, pfun, pdata);
}

void scan_spoly3(Poly *p, int n, Paint *pfun, void *pdata)
{
  Edge *lft, *rgt, *seg, l, r, s;
  int lv, rv, tv = first_vertex(p->v, n);

  rgt = edge(p->v[tv], p->v[rv = NEXT(tv,n)], 'y', &r);
  lft = edge(p->v[tv], p->v[lv = PREV(tv,n)], 'y', &l);
  
  while (lft && rgt) {
    seg = edge(lft->p, rgt->p, 'x', &s);
    do {
      pfun(seg->p, n, lv, lft->t, rv, rgt->t, seg->t, pdata);
    } while (seg = increment(seg));
    if (!(rgt = increment(rgt))) { tv = rv;
      rgt = increment(edge(p->v[tv], p->v[rv = NEXT(rv,n)], 'y', &r));
    }
    if (!(lft = increment(lft))) { tv = lv;
      lft = increment(edge(p->v[tv], p->v[lv = PREV(lv,n)], 'y', &l));
    }
  }
}

static int first_vertex(Vector3 v[], int n)
{
  if (v[0].y < v[n-1].y)
    return ((v[0].y < v[n].y)? 0: n);
  else
    return ((v[n-1].y < v[n].y)? n-1: n);
}

static Edge *edge(Vector3 p0, Vector3 p1, char c, Edge *e)
{
  SNAP_XY(p0); SNAP_XY(p1);
  switch (c) {
  case 'x': e->n = ABS(p1.x - p0.x); break;
  case 'y': e->n = p1.y - p0.y; break;
  }
  e->t = 0;
  e->p = p0;
  e->d = (e->n < 1) ? 0.0 : 1.0 / e->n;
  e->i = v3_scale(e->d, v3_sub(p1, p0));
  return e;
}

static Edge *increment(Edge *e)
{
  e->p = v3_add(e->p, e->i);
  e->t += e->d;
  return (e->n-- > 0) ? e : (Edge *)0;
}

Vector3 seg_bilerp(Poly *p, int n, Real t, int lv, Real lt, int rv, Real rt)
{
  return v3_bilerp(t,lt,p->v[NEXT(lv,n)],p->v[lv],rt,p->v[PREV(rv,n)],p->v[rv]);
}
