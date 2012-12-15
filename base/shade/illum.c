#include <stdio.h>
#include <math.h>
#include "shade.h"

Color ambient(RContext *rc)
{
  Light *l;
  Color c = C_BLACK;

  for (l = rc->l; l != NULL; l = l->next)
      c = c_add(c, c_scale(l->ambient, l->color));
  return c;
}


Color diffuse(RContext *rc)
{
  Light *l;
  Color c = C_BLACK;
  Cone receiver = cone_make(rc->p, rc->n, PI/2);

  for (l = rc->l; l != NULL; l = l->next)
    if ((*l->transport)(l, receiver, rc))
      c = c_add(c, c_scale(v3_dot(l->outdir, rc->n), l->outcol));
  return c;
}


Color specular(RContext *rc)
{
  Light *l;
  Vector3 h;
  Color c = C_BLACK;
  Cone receiver = cone_make(rc->p, rc->n, PI/2);

  for (l = rc->l; l != NULL; l = l->next) {
    if ((*l->transport)(l, receiver, rc)) {
      h = v3_unit(v3_add(l->outdir, rc->v));
      c = c_add(c, c_scale(pow(MAX(0, v3_dot(h, rc->n)),rc->m->se),l->outcol));
    }
  }
  return c;
}
