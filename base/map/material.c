#include <stdio.h>
#include <math.h>
#include "rshade.h"
#include "map.h"


Color textured_plastic(RContext *rc)
{
  Color c, ct = texture_map(rc->m->tinfo, rc->t);

  c = c_add(c_mult(ct, c_add(c_scale(rc->m->ka, ambient(rc)),
                             c_scale(rc->m->kd, diffuse(rc)))),
            c_mult(rc->m->s, c_scale(rc->m->ks, specular(rc))));
  return c;
}

Color rough_surface(RContext *rc)
{
  Vector3 d = bump_map(rc->m->tinfo, rc->t, rc->n, rc->du, rc->dv);
  rc->n = v3_unit(v3_add(rc->n, d));
  return matte(rc);
}


Color shiny_surface(RContext *rc)
{
  Color ce = environment_map(rc->m->tinfo, reflect_dir(rc->v, rc->n));

  return c_add(c_scale(rc->m->ka, ambient(rc)),
            c_scale(rc->m->ks, c_add(ce, specular(rc))));
}

