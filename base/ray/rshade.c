#include <math.h>
#include "rshade.h"
#include "rt.h"

#define MAX_RAY_LEVEL 4
#define RAY_WF_MIN 0.08
#define BG_COLOR C_BLACK


Color ray_shade(int level, Real w, Ray v, RContext *rc, Object *ol)
{
  Inode *i = ray_intersect(ol, v);
  if (i != NULL) { Light *l; Real wf;
    Material *m = i->m;
    Vector3 p = ray_point(v, i->t); 
    Cone  recv = cone_make(p, i->n, PIOVER2);
    Color c = c_mult(m->c, c_scale(m->ka, ambient(rc)));
    rc->p = p;

    for (l = rc->l; l != NULL; l = l->next) 
      if ((*l->transport)(l, recv, rc) && (wf = shadow(l, p, ol)) > RAY_WF_MIN)
	c = c_add(c, c_mult(m->c,
		     c_scale(wf * m->kd * v3_dot(l->outdir,i->n), l->outcol)));

    if (level++ < MAX_RAY_LEVEL) {
      if ((wf = w * m->ks) > RAY_WF_MIN) {
	Ray r = ray_make(p, reflect_dir(v.d, i->n));
        c = c_add(c, c_mult(m->s,
		     c_scale(m->ks, ray_shade(level, wf, r, rc, ol))));
      }
      if ((wf = w * m->kt) > RAY_WF_MIN) {
	Ray t = ray_make(p, refract_dir(v.d, i->n, (i->enter)? 1/m->ir: m->ir));
	if (v3_sqrnorm(t.d) > 0) {
	  c = c_add(c, c_mult(m->s,
		       c_scale(m->kt, ray_shade(level, wf, t, rc, ol))));
	}
      }
    }
    inode_free(i); 
    return c;
  } else {
    return BG_COLOR;
  }
}


Vector3 reflect_dir(Vector3 d, Vector3 n)
{
  return v3_add(d, v3_scale(-2 * v3_dot(n, d), n));
}


Vector3 refract_dir(Vector3 d, Vector3 n, Real eta)
{
  Real c1, c2;

  if ((c1 = v3_dot(d, n)) < 0)
    c1 = -c1;
  else
    n = v3_scale(-1.0, n);

  if ((c2 = 1 - SQR(eta) * (1 - SQR(c1))) < 0)
    return v3_make(0,0,0);
  else
    return v3_add(v3_scale(eta, d), v3_scale(eta*c1 - sqrt(c2), n));
}


Real shadow(Light *l, Vector3 p, Object *ol)
{
  Real t, kt; Inode *i; Vector3 d;

  if (l->type == LIGHT_AMBIENT)
    return 1.0;
  d = (l->type == LIGHT_DISTANT)? l->dir : v3_sub(l->loc, p);

  if ((i = ray_intersect(ol, ray_make(p, d))) == NULL)
    return 1.0;
  t = i->t; kt = i->m->kt; inode_free(i);

  if (l->type == LIGHT_DISTANT && t > RAY_EPS)
    return kt;
  else if (l->type != LIGHT_DISTANT && t > RAY_EPS && t < 1)
    return kt;
  else
    return 1.0;
}

