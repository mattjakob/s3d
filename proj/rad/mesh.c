#include "geom.h"
#include "poly.h"

static Poly *plist = NULL;

static void tri_refine(Vector3 v0, Vector3 v1, Vector3 v2, Real s, int maxrec)
{
  Real l1 = v3_norm(v3_sub(v0, v1));
  Real l2 = v3_norm(v3_sub(v1, v2));
  Real l3 = v3_norm(v3_sub(v2, v0));

  if ((MAX(l1, MAX(l2, l3))) <= s || --maxrec < 0) {
    plist = poly_insert(plist, poly3_make(v0, v1, v2));
  } else {
    Vector3 m1 = v3_scale(0.5, v3_add(v0, v1));
    Vector3 m2 = v3_scale(0.5, v3_add(v1, v2));
    Vector3 m3 = v3_scale(0.5, v3_add(v2, v0));

    tri_refine(m1, v1, m2, s, maxrec);
    tri_refine(m2, v2, m3, s, maxrec);
    tri_refine(m3, v0, m1, s, maxrec);
    tri_refine(m1, m2, m3, s, maxrec);
  }
}

Poly *plist_refine(Poly *p, Real s, int maxrec)
{
  plist = NULL;
  while (p != NULL) {
    tri_refine(p->v[0], p->v[1], p->v[2], s, maxrec);
    p = p->next;
  }
  return plist;
}

