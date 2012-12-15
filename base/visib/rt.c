#include "rt.h"


Inode *ray_intersect(Object *olist, Ray r)
{
  Object *o; Poly *p;
  Inode *l = NULL, *i = NULL;

  for (o = olist; o != NULL; o = o->next ) {
    p  = (o->type == V_POLYLIST)? o->u.pols : NULL;
    do {
      switch (o->type) {
      case V_CSG_NODE:
	l = csg_intersect(o->u.tcsg, r); break;
      case V_PRIM:
	l = prim_intersect(o->u.prim, r); break;
      case V_POLYLIST:
	if (p != NULL) {
	  l = poly_intersect(p, poly3_plane(p), r);
	  p = p->next;
	} break;
      }
      if ((l != NULL) && (i == NULL || l->t < i->t)) {
	if (i != NULL) inode_free(i);
	i = l;
	i->m = o->mat;
      }
    } while (p != NULL);
  }
  for (l = i; l != NULL; l = l->next)
    l->m = i->m;
  return i;
}
