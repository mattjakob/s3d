#include <stdio.h>
#include <math.h>
#include "shade.h"


Color constant(RContext *rc)
{
  return rc->m->c;
}


Color matte(RContext *rc)
{
  return c_mult(rc->m->c, c_add(c_scale(rc->m->ka, ambient(rc)),
				c_scale(rc->m->kd, diffuse(rc))));
}


Color metal(RContext *rc)
{
  return c_mult(rc->m->c, c_add(c_scale(rc->m->ka, ambient(rc)),
				c_scale(rc->m->ks, specular(rc))));
}


Color plastic(RContext *rc)
{
  return c_add(c_mult(rc->m->c, c_add(c_scale(rc->m->ka, ambient(rc)),
				      c_scale(rc->m->kd, diffuse(rc)))),
	       c_mult(rc->m->s, c_scale(rc->m->ks, specular(rc))));
}



