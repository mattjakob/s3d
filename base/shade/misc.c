#include <stdio.h>
#include <math.h>
#include "shade.h"


Cone cone_make(Vector3 o, Vector3 d, Real angle)
{
  Cone c;
  c.o = o; c.d = d; c.cosa = cos(angle);
  return c;
}


int dir_coupling(Cone a, Vector3 v)
{
  if (v3_dot(a.d, v3_scale(-1, v)) >= a.cosa)
    return TRUE;
  else
    return FALSE;
}

int point_coupling(Cone a, Cone b)
{
  Vector3 d = v3_unit(v3_sub(a.o, b.o));
  return dir_coupling(a, d) && dir_coupling(b, v3_scale(-1, d));
}


Light *light_ambient(Real amb)
{
  Light *l = NEWSTRUCT(Light);
  l->type = LIGHT_AMBIENT;
  l->color = C_WHITE;
  l->ambient = amb;
  l->transport = ambientlight;
  l->tinfo = NULL;
  return l;
}


Material *mat_default()
{
  Material *m = NEWSTRUCT(Material);
  m->c = C_WHITE;
  m->ka = .1;
  m->kd = .9;
  m->luminance = matte;
  m->tinfo = NULL;
  return m;
}

RContext *rc_tset(RContext *rc, Vector3 v, Vector3 p, Vector3 n,
		  Vector3 t, Vector3 du, Vector3 dv, Material *m)
{
  rc->v = v;
  rc->p = p;
  rc->n = n;
  rc->t = t;
  rc->du = du;
  rc->dv = dv;
  rc->m = m;
  return rc;
}

RContext *rc_set(RContext *rc, Vector3 v, Vector3 p, Vector3 n,	Material *m)
{
  rc->p = p;
  rc->n = n;
  rc->v = v;
  rc->m = m;
  return rc;
}

RContext *rc_sset(RContext *rc, View *c, Light *l, Image *img)
{
  rc->c = c;
  rc->l = l;
  rc->img = img;
  return rc;
}
