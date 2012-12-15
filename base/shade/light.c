#include <stdio.h>
#include <math.h>
#include "shade.h"


int ambientlight(Light *l, Cone recv, RContext *rc)
{
  return FALSE;
}


int distantlight(Light *l, Cone recv, RContext *rc)
{
  if (dir_coupling(recv, v3_scale(-1, l->dir)) == FALSE)
    return FALSE;
  l->outdir = l->dir;
  l->outcol = c_scale(l->intensity, l->color);
  return TRUE;
}


int pointlight(Light *l, Cone recv, RContext *rc)
{
  Real d, dist, atten;
  Vector3 v = v3_sub(rc->p, l->loc);
  dist = v3_norm(v);
  l->dir = v3_scale(1/dist, v);
  if (dir_coupling(recv, l->dir) == FALSE)
    return FALSE;
  atten = ((d = l->att0 + l->att1*dist + l->att2*SQR(dist)) > 0)? 1/d : 1;
  l->outdir = v3_scale(-1, l->dir);
  l->outcol = c_scale(l->intensity * atten, l->color);
  return TRUE;
}


int spotlight(Light *l, Cone recv, RContext *rc)
{
  Vector3 v;
  Real d, dist, atten;

  if (point_coupling(recv, cone_make(l->loc, l->dir, l->cutoff)) == FALSE)
    return FALSE;

  v = v3_sub(rc->p, l->loc);
  dist = v3_norm(v);
  atten = ((d = l->att0 + l->att1*dist + l->att2*SQR(dist)) > 0)? 1/d : 1;
  if ((d = v3_dot(v3_scale(1/dist, v), l->dir)) > 0)
    atten *= pow(d, l->distr);
  l->outdir = v3_scale(-1/dist, v);
  l->outcol = c_scale(l->intensity * atten, l->color);
  return TRUE;
}

