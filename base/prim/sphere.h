#ifndef SPHERE_H
#define SPHERE_H

#include "sdltypes.h"

typedef struct Sphere {
  Vector3 c;
  double  r;
} Sphere;


struct Prim *sphere_set(Prim *p, Vector3 c, double  r);
void sphere_destroy(Prim *p);
struct Prim *sphere_instance(PrimFuncs *f);
Box3d sphere_bbox(Prim *p);
int sphere_classify(Prim *p, Vector3 q);
Vector3 sphere_point(Prim *p, Real u, Real v);
Vector3 sphere_normal(Prim *p, Real u, Real v);
Vector3 sphere_gradient(Prim *p, Vector3 q);
Inode *sphere_intersect(Prim *p, Ray r);
Prim *sphere_transform(Prim *p, Matrix4 md, Matrix4 mi);
Poly *sphere_uv_decomp(Prim *p, Real level);
Vector3 sphere_texc(Prim *p, Real u, Real v);
Vector3 sphere_du(Prim *p, Real u, Real v);
Vector3 sphere_dv(Prim *p, Real u, Real v);
Matrix4 sphere_local(Prim *p);
int sphere_id(Prim *p);
void sphere_write(Prim *p, FILE *fp);
void sphere_draw(Prim *p, int axis);
Val sphere_parse(int c, Pval *pl);

extern PrimFuncs sphere_funcs;

#endif
