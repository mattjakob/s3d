#include <stdio.h>
#include <math.h>
#include "map.h"

Color texture_default()
{
  return c_make(1,1,1);
}


Color texture_map(void *info, Vector3 t)
{
  TmapInfo *i = info;

  switch (i->code) {
  case TMAP_TILE:
    t.x = mod(t.x, 1); t.y = mod(t.y, 1);
    break;
  case TMAP_CLAMP:
  default:
    if (t.x < 0 || t.x > 1 || t.y < 0 || t.y > 1)
      return i->bg;
    break;
  }
  return (*i->src->texfunc)(i->src->texdata, t);
}

Real texture_c1(Color c)
{
  return c.x;
}

Real fderiv(Real f0, Real f1, Real h)
{
  return (f1 - f0)/h;
}

Color bump_map(void *info, Vector3 t, Vector3 n, Vector3 ds, Vector3 dt)
{
  TextureSrc *src = info;
  Real h = 0.0005;

  Real fo = texture_c1((*src->texfunc)(src->texdata, t));
  Real fu = texture_c1((*src->texfunc)(src->texdata, v3_add(t,v3_make(h,0,0))));
  Real fv = texture_c1((*src->texfunc)(src->texdata, v3_add(t,v3_make(0,h,0))));

  Real du = fderiv(fo, fu, h);
  Real dv = fderiv(fo, fv, h);
  
  Vector3 u = v3_scale(du, v3_cross(n, dt));
  Vector3 v = v3_scale(-dv, v3_cross(n, ds));

  return v3_add(u, v);
}

Vector3 sph_coord(Vector3 r)
{
  Real len = v3_norm(r);
  Real theta = atan2(r.y/len, r.x/len);
  Real phi = asin(r.z/len);

  return v3_make(theta, phi, len);
}  

Color environment_map(void *info, Vector3 r)
{
  TextureSrc *src = info;

  Vector3 t = sph_coord(r);
  t.x = (t.x / PITIMES2) + 0.5; t.y = (t.y / PI) + 0.5;

  return (*src->texfunc)(src->texdata, t);
}

Color chrome_map(void *info, Vector3 r)
{
  TextureSrc *src = info;

  Vector3 t = v3_unit(r);
  t.x = (t.x / 2) + .5; t.y = (t.y / 2) + .5; 

  return (*src->texfunc)(src->texdata, t);
}

