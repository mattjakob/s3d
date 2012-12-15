#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "radiosity.h"

static int  max_iter = 10;
static int  vis_flag = TRUE;
static Real dm_eps = 0.001;


static void initialize(int n, Color *m, Color *dm, Real * a, Poly **p, Color *e)
{
  int i;
  for (i = 0; i < n; i++) {
    a[i] = poly3_area(p[i]);
    m[i] = dm[i] = e[i];
  }
}

static int select_shooter(int n, Color *dm, Real *a)
{
  Real m, mmax;
  int i, imax;

  for (i = 0; i < n; i++) {
    m = c_sqrnorm(c_scale(a[i], dm[i]));
    if (i == 0 || m > mmax) {
      mmax = m;
      imax = i;
    }
  }
  return  imax;
}

static int converged(int i, Color *dm)
{
  return (c_sqrnorm(dm[i]) < dm_eps);
}

static Real visible(int n, Poly **p, Vector3 v, Vector3 d)
{
  Ray r = ray_make(v, d);

  while (n--) {
    Real t = poly3_ray_inter(p[n], poly3_plane(p[n]), r);
    if (t > REL_EPS && t < 1)
      return 0.0;
  }
  return 1.0;
}

static Real formfactor(int i, int j, int n, Poly **p, Real *a)
{
  Vector3 vi, vj, vji, d;
  Real r2, ci, cj;
 
  vi = poly_centr(p[i]);
  vj = poly_centr(p[j]);
  vji = v3_sub(vi, vj);
  if ((r2 = v3_sqrnorm(vji)) < REL_EPS)
    return 0;    
  d = v3_scale(1.0/sqrt(r2), vji);
  if ((cj =  v3_dot(poly_normal(p[j]), d)) < REL_EPS)
    return 0;
  if ((ci = -v3_dot(poly_normal(p[i]), d)) < REL_EPS)
    return 0;
  if (vis_flag  && visible(n, p, vj, vji) < REL_EPS)
    return 0;
  return a[i] * ((cj * ci) / (PI * r2 + a[i])); 
}

static Color ambient_rad(int n, Color *dm, Real *a)
{
  int i;
  Real aa = 0;
  Color ma = c_make(0,0,0);
  for (i = 0; i < n; i++) {
    ma = c_add(ma, c_scale(a[i], dm[i]));
    aa += a[i];
  }
  return c_scale(1.0/aa, ma);
}


void radiosity_set(Real e, int iter, int vis)
{
  if (iter < 0 || e < 0)
    error("(radiosity) invalid parameters");
  dm_eps = SQR(3*e); max_iter = iter; vis_flag = vis;
}
  

Color *radiosity_prog(int n, Poly **p, Color *e, Color *rho)
{
  int src, rcv, iter = 0;
  Real ff, mts, *a = NEWTARRAY(n, Real);
  Color d, *dm = NEWTARRAY(n, Color);
  Color ma, *m = NEWTARRAY(n, Color);
	
  initialize(n, m, dm, a, p, e);
  while (iter-- < max_iter) {
    src = select_shooter(n, dm, a);
    if (converged(src, dm))
      break;
    for (rcv = 0; rcv < n; rcv++) {
      if (rcv == src || (ff = formfactor(src, rcv, n, p, a)) < REL_EPS)
	continue;
      d = c_scale(ff, c_mult(rho[rcv], dm[src]));

      m[rcv] = c_add(m[rcv], d);
      dm[rcv] = c_add(dm[rcv], d);
    }
    dm[src] = c_make(0,0,0);
  }
  ma = ambient_rad(n, dm, a);
  for (rcv = 0; rcv < n; rcv++)
    m[rcv] = c_add(m[rcv], ma);
  efree(a), efree(dm);
  return m;
}
