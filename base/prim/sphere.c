#include <stdio.h>
#include <math.h>
#include "lang.h"
#include "prim.h"
#include "poly.h"
#include "sphere.h"


PrimFuncs sphere_funcs = {
  sphere_instance,
  sphere_destroy,
  sphere_bbox,
  sphere_classify,
  sphere_point,
  sphere_normal,
  sphere_gradient,
  sphere_intersect,
  sphere_transform,
  sphere_uv_decomp,
  sphere_texc,
  sphere_du,
  sphere_dv,
  sphere_local,
  sphere_id,
  sphere_write,
  sphere_draw,
};


Prim *sphere_instance(PrimFuncs *f)
{
  Vector3 ll = {-1,-1,-1}, ur = {1,1,1};
  Prim *p = NEWSTRUCT(Prim);
  Sphere *s = NEWSTRUCT(Sphere);

  p->f = f;
  p->b.ll = ll; p->b.ur = ur;
  p->ti = p->td = m4_ident();
  s->c = v3_make(0,0,0); s->r = 1;
  p->d = s;
  return p;
}

void sphere_destroy(Prim *p)
{
  efree(p->d);
  efree(p);
}

Prim *sphere_set(Prim *p, Vector3 c, double  r)
{
  Sphere *s = p->d;
  s->c = c; s->r = r;
  p->ti = p->td = m4_ident();
  p = sphere_transform(p, m4_scale(r,r,r), m4_scale(1/r,1/r,1/r)); 
  p = sphere_transform(p, m4_translate(c.x,c.y,c.z), m4_translate(-c.x,-c.y,-c.z));
  p->b = sphere_bbox(p);
  return p;
}


Box3d sphere_bbox(Prim *p)
{
  Box3d b;
  Vector3 v;
  double x, y, z;

  for (x = -1; x <= 1; x +=2) {
    for (y = -1; y <= 1; y +=2) {
      for (z = -1; z <= 1; z +=2) {
	v = v3_m4mult(v3_make(x, y, z), p->td);
	if (x == -1 && y == -1 && z == -1) {
	  b.ll = b.ur = v;
	} else {
	  if (v.x < b.ll.x) b.ll.x = v.x;
	  if (v.y < b.ll.y) b.ll.y = v.y;
	  if (v.z < b.ll.z) b.ll.z = v.z;
	  if (v.x > b.ur.x) b.ur.x = v.x;
	  if (v.y > b.ur.y) b.ur.y = v.y;
	  if (v.z > b.ur.z) b.ur.z = v.z;
	}	
      }
    }
  }
  return b;
}


int sphere_classify(Prim *p, Vector3 q)
{
  Vector3 w = v3_m4mult(q, p->ti);
  Real d = v3_norm(w);
  return (d < 1)? PRIM_IN : ((d > 1)? PRIM_OUT : PRIM_ON);
}


Vector3 sphere_point(Prim *p, Real u, Real v)
{
  Vector3 w;
  w.x = cos(u)*cos(v);
  w.y = sin(u)*cos(v);
  w.z = sin(v);
  return v3_m4mult(w, p->td);
}


Vector3 sphere_normal(Prim *p, Real u, Real v)
{
  Vector3 w;
  w.x = cos(u)*cos(v);
  w.y = sin(u)*cos(v);
  w.z = sin(v);
  return v3_m3mult(w, m4_transpose(p->ti));
}


Vector3 sphere_gradient(Prim *p, Vector3 q)
{
  Vector3 w = v3_m4mult(q, p->ti);
  return v3_m3mult(v3_scale(2., w), m4_transpose(p->ti));
}


Inode *sphere_intersect(Prim *p, Ray ro)
{
  double a, b, c, disc, t0, t1;
  Inode *i0, *i1;
  Ray r = ray_transform(ro, p->ti);

  a = v3_sqrnorm(r.d);
  b = 2 * v3_dot(r.d, r.o);
  c = v3_sqrnorm(r.o) - 1;
  if ((disc = SQR(b) - 4 * a * c) <= 0)
    return (Inode *)0;
  t0 = (-b - sqrt(disc)) / (2 * a);
  t1 = (-b + sqrt(disc)) / (2 * a);
  if (t1 < RAY_EPS)
    return (Inode *)0;
  if (t0 < RAY_EPS) {
    Vector3 n1 = v3_unit(sphere_gradient(p, ray_point(r, t1)));
    return inode_alloc(t1, n1, FALSE);
  } else {
    Vector3 n0 = v3_unit(sphere_gradient(p, ray_point(ro, t0)));
    Vector3 n1 = v3_unit(sphere_gradient(p, ray_point(ro, t1)));
    i0 = inode_alloc(t0, n0, TRUE);
    i1 = inode_alloc(t1, n1, FALSE);
    i0->next = i1;
    return i0;
  }
}


Prim *sphere_transform(Prim *p, Matrix4 md, Matrix4 mi)
{
  p->td = m4_m4prod(md, p->td);
  p->ti = m4_m4prod(p->ti, mi);
  return p;
}

#define UMIN (0)
#define UMAX (PITIMES2)
#define ULEN (UMAX - UMIN)
#define VEPS (0.02)
#define VMIN ((PI/2.0) + VEPS )
#define VMAX (PI + (PI/2.0) - VEPS)
#define VLEN (VMAX - VMIN)


Poly *sphere_uv_decomp(Prim *p, Real level)
{
  int i, j, nu = 20 * level, nv = 10 * level;
  Real u, v, iu = ULEN/(Real)nu, iv = VLEN/(Real)nv;
  Poly *l = NULL;

  for (u = UMIN, i = 0; i < nu; u += iu, i++) {
    for (v = VMIN, j = 0; j < nv; v += iv, j++) {
      l = poly_insert(l,
               poly3_make(v3_make(u,v,0),v3_make(u,v+iv,0),v3_make(u+iu,v,0)));
      l = poly_insert(l,
               poly3_make(v3_make(u+iu,v+iv,0),v3_make(u+iu,v,0),v3_make(u,v+iv,0)));
    }
  }
  return l;
}

Vector3 sphere_texc(Prim *p, Real u, Real v)
{
  return v3_make((u - UMIN)/ULEN, (v - VMIN)/VLEN, 0);
}

Vector3 sphere_du(Prim *p, Real u, Real v)
{
  return v3_make(- sin(u) * cos(v), cos(u) * cos(v), 0);
}

Vector3 sphere_dv(Prim *p, Real u, Real v)
{
  return v3_make(- cos(u) * sin(v), - sin(u) * sin(v), cos(v));
}

Matrix4 sphere_local(Prim *p)
{
  return p->ti;
}


int sphere_id(Prim *p)
{
  return SPHERE;
}

void sphere_write(Prim *p, FILE *fp)
{
  Sphere *s = p->d;
  fprintf(fp, "sphere { \n");
  fprintf(fp, "\t\t center = {%g, %g, %g},\n",s->c.x,s->c.y,s->c.z);
  fprintf(fp, "\t\t radius = %g \n}\n",s->r);
}

void sphere_draw(Prim *p, int axis)
{
  Vector3 v[5];
  Box3d b;
  int i;
  
  b = sphere_bbox(p);
  // ortho_plot_bbox(b, axis);
}


Val sphere_parse(int pass, Pval *pl)
{
  Val v = {V_NULL, 0};

  if (pass == T_EXEC) {
    Vector3 c = pvl_get_v3(pl, "center", v3_make(0,0,0));
    double r = pvl_get_num(pl, "radius", 1);
    v.type = V_PRIM;
    sphere_set(v.u.v = sphere_instance(&sphere_funcs), c, r);
  }
  return v;
}
