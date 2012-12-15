#include <stdio.h>
#include <math.h>
#include "defs.h"
#include "geom.h"
#include "poly.h"
#include "clip.h"


int is_backfacing(Poly *p, Vector3 v)
{
  return (v3_dot(poly_normal(p), v) >= 0)? TRUE : FALSE;
}

int clipcode(Real h, Vector3 v)
{
  int c = 0;
  if (v.y >  v.z) c |=  01;
  if (v.y < -v.z) c |=  02;
  if (v.x >  v.z) c |=  04;
  if (v.x < -v.z) c |= 010;
  if (v.z >   1 ) c |= 020;
  if (v.z <   h ) c |= 040;
  return(c);
}

int inside_frustrum(Real h, Vector3 v)
{
  return (clipcode(h, v) == 0);
}

int cull_poly3(Real h, Poly *p)
{
  int i, c[3];
  for (i = 0; i < p->n; i++)
    c[i] = clipcode(h, p->v[i]);
  return (c[0] & c[1] & c[2]);
}

