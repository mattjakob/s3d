#include "poly.h"

static int max3_index(Real d1, Real d2, Real d3);


Poly *poly_alloc(int n)
{
  Poly *p = NEWSTRUCT(Poly);
  p->n = n;
  p->v = NEWARRAY(n, Vector3);
  p->next = NULL;
  return p;
}

Poly *poly_transform(Poly *p, Matrix4 m)
{
  int i;
  for (i = 0; i < p->n; i++)
    p->v[i] = v3_m4mult(p->v[i], m);
  return p;
}

Poly *poly_homoxform(Poly *p, Matrix4 m)
{
  int i;
  for (i = 0; i < p->n; i++)
    p->v[i] = v3_v4conv(v4_m4mult(v4_v3conv(p->v[i]), m));
  return p;
}

Vector3 poly_normal(Poly *p)
{
  return v3_unit(v3_cross(v3_sub(p->v[1], p->v[0]), v3_sub(p->v[2], p->v[0])));
}

Vector3 poly_centr(Poly *p)
{
  int i;  Vector3 c = v3_make(0,0,0);
  for (i = 0; i < p->n; i++)
    c = v3_add(c, p->v[i]);
  return v3_scale(1. / (p->n), c);
}

int poly_copy(Poly *s, Poly *d)
{
  int i;
  for (i = 0; i < s->n; i++)
    d->v[i] = s->v[i];
  return (d->n = s->n);
}

Poly *poly_insert(Poly *pl, Poly *p)
{
  p->next = pl;
  return p;
}

Inode *poly_intersect(Poly *p, Vector4 plane, Ray r)
{
  Real t = poly3_ray_inter(p, plane, r);
  if (t < RAY_EPS) {
    return NULL;
  } else {
    Vector3 n = v3_make(plane.x, plane.y, plane.z);
    return inode_alloc(t, n, (v3_dot(n, r.d) < 0));
  }
}

#define MINUS_INFTY (-MAX_INT)

static Real plane_ray_inter(Vector4 h, Ray r)
{
  Vector3 n = {h.x, h.y, h.z};
  Real denom = v3_dot(n, r.d);
  if (REL_EQ(denom, 0))
    return MINUS_INFTY;
  else 
    return -(v3_dot(n, r.o) + h.w) / denom;
}

#define PROJ_BASE(A, B, Q0_S, Q0_T, Q1_S, Q1_T, Q2_S, Q2_T) \
{ Real d = (Q1_S * Q2_T - Q2_S * Q1_T); \
       A = (Q0_S * Q2_T - Q2_S * Q0_T) / d;  \
       B = (Q1_S * Q0_T - Q0_S * Q1_T) / d;  \
}

Real poly3_ray_inter(Poly *p, Vector4 plane, Ray r)
{
  Vector3 q0, q1, q2;
  Real t, d, a, b;

  t = plane_ray_inter(plane, r);
  if (t < RAY_EPS)
    return MINUS_INFTY;

  q0 = v3_sub(ray_point(r, t), p->v[0]);
  q1 = v3_sub(p->v[1], p->v[0]);
  q2 = v3_sub(p->v[2], p->v[0]);

  switch (max3_index(fabs(plane.x), fabs(plane.y), fabs(plane.z))) {
  case 1:
    PROJ_BASE(a, b, q0.y, q0.z, q1.y, q1.z, q2.y, q2.z); break;
  case 2:
    PROJ_BASE(a, b, q0.x, q0.z, q1.x, q1.z, q2.x, q2.z); break;
  case 3:
    PROJ_BASE(a, b, q0.x, q0.y, q1.x, q1.y, q2.x, q2.y); break;
  }
  if ((a >= 0 && b >= 0 && (a+b) <= 1))
    return t;
  else
    return MINUS_INFTY;
}

Poly *poly3_make(Vector3 v0, Vector3  v1, Vector3  v2)
{
  Poly *p = poly_alloc(3);
  p->v[0] = v0;  p->v[1] = v1;  p->v[2] = v2; 
  return p;
}

Vector4 poly3_plane(Poly *p)
{
  Vector3 n = poly_normal(p);
  Real d = -v3_dot(n, p->v[0]);
  return v4_make(n.x, n.y, n.z, d);
}

Real poly3_area(Poly *p)
{
  return v3_norm(v3_cross(v3_sub(p->v[1],p->v[0]), v3_sub(p->v[2],p->v[0])))/2;
}

int poly3_read(Poly *p, FILE* fp)
{
  char *fmt = "{%lf, %lf, %lf},";
  int i, n;

  fscanf(fp,"{");
  for (i = 0; i < 3; i++) {
    if ((n=fscanf(fp, fmt,&(p->v[i].x),&(p->v[i].y),&(p->v[i].z))) == EOF)
      return EOF;
    else if (n != 3)
      error("Error reading polyfile");
    fscanf(fp,"}\n");
  }
  return (p->n = 3);
}


void poly3_write(Poly *p, FILE* fp)
{
  if ( (v3_norm(v3_sub(p->v[0], p->v[1])) < EPS)
      ||(v3_norm(v3_sub(p->v[1], p->v[2])) < EPS)
      ||(v3_norm(v3_sub(p->v[2], p->v[0])) < EPS))
    warning("(poly3_write) degenerate polygon");
  fprintf(fp, "{{%g, %g, %g}, ",  p->v[0].x, p->v[0].y, p->v[0].z);
  fprintf(fp, " {%g, %g, %g}, ",  p->v[1].x, p->v[1].y, p->v[1].z);
  fprintf(fp, " {%g, %g, %g}}\n", p->v[2].x, p->v[2].y, p->v[2].z);
}


Poly *poly3_decode(Pval *plist)
{
  Pval *pl;
  int k;

  for (pl = plist, k = 0; pl !=NULL; pl = pl->next, k++)
    ;
  if (k != 3) {
    error("(poly3) wrong number of vertices");
  } else {
    Poly *t = poly_alloc(3);
    for (pl = plist, k = 0; pl !=NULL; pl = pl->next, k++)
      if (pl->val.type == V_PVL)
	t->v[k] = pvl_to_v3(pl->val.u.v);
      else
	error("(poly3) error in vertex");
    return t;
  }
}


void trilist_write(Poly *tlist, FILE* fp)
{
  Poly *p = tlist;
  
  fprintf(fp, "trilist {\n");
  while (p != NULL) {
    poly3_write(p, fp);
    if ((p = p->next) != NULL)
      fprintf(fp, ",\n");
  }
  fprintf(fp, "}\n");
}


Val trilist_parse(int pass, Pval *plist)
{
  Val v = {V_NULL, 0};

  if (pass == T_EXEC) {
    Pval *pl;
    Poly *tl = NULL;

    for (pl = plist; pl != NULL; pl = pl->next) {
      if (pl->val.type == V_PVL)
	tl = poly_insert(tl, poly3_decode(pl->val.u.v));
      else
	error("(trilist) syntax error");
    }
    v.type = V_POLYLIST;
    v.u.v = tl;
  }
  return v;
}

int plist_lenght(Poly *l)
{
  int n = 0;
  while (l != NULL) {
    n++; l = l->next;
  }
  return n;
}

Poly *plist_alloc(int n, int m)
{
  Poly *l = NULL;
  while (n--)
    l = poly_insert(l, poly_alloc(m));
  return l;
}

void plist_free(Poly *l)
{
  Poly *q, *p = l;
  while (p != NULL) {
    q = p;
    p = p->next;
    efree(q->v);
    efree(q);
  }
}

Poly *plist_transform(Poly *l, Matrix4 m)
{
  Poly *p;
  for (p = l; p != NULL; p = p->next)
    poly_transform(p, m);
  return l;
}

static int max3_index(Real d1, Real d2, Real d3)
{
  if (d1 > d2)
    return (d1 > d3)? 1 : 3;
  else
    return (d2 > d3)? 2 : 3;
}

