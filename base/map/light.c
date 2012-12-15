#include <stdio.h>
#include <math.h>
#include "map.h"


int slide_projector(Light *l, Cone recv, RContext *rc)
{
  Vector3 c, v, t, m;
  TslideInfo *ti = l->tinfo;

  if (point_coupling(recv, cone_make(l->loc, l->dir, l->cutoff)) == FALSE)
    return FALSE;

  v = v3_sub(rc->p, l->loc);
  m = v3_make(v3_dot(v, ti->u), v3_dot(v, ti->v), v3_dot(v, l->dir));
  t = v3_make(m.x / m.z * l->distr, m.y / m.z * l->distr, m.z);
  t.x = t.x * 0.5 + 0.5; t.y = t.y * 0.5 + 0.5;
  c = (*ti->src->texfunc)(ti->src->texdata, t);

  l->outdir = v3_scale(-1, v3_unit(v));
  l->outcol = c_scale(l->intensity, c);
  return TRUE;
}

