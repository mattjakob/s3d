#ifndef PRIM_H
#define PRIM_H

#include "geom.h"
#include "poly.h"
#include "ray.h"
#include "lang.h"
#include "sdltypes.h"


typedef struct Prim {
  struct PrimFuncs *f;
  Box3d   b;
  Matrix4 td, ti;
  void  *d;
} Prim;

typedef struct PrimFuncs {
  Prim   *(*instance)();
  void    (*destroy)();
  Box3d   (*bbox)();
  int     (*classify)();
  Vector3 (*point)();
  Vector3 (*normal)();
  Vector3 (*gradient)();
  Inode  *(*intersect)();
  Prim   *(*transform)();
  Poly   *(*uv_decomp)();
  Vector3 (*texc)();
  Vector3 (*du)();
  Vector3 (*dv)();
  Matrix4 (*local)();
  int     (*id)();
  void    (*write)();
  void    (*draw)();
} PrimFuncs;


Prim *prim_instance(PrimFuncs *f);
void prim_destroy(Prim *p);
Box3d prim_bbox(Prim *p);
int prim_classify(Prim *p, Vector3 q);
Vector3 prim_point(Prim *p, Real u, Real v);
Vector3 prim_normal(Prim *p, Real u, Real v);
Vector3 prim_gradient(Prim *p, Vector3 q);
Inode *prim_intersect(Prim *p, Ray r);
Prim *prim_transform(Prim *p, Matrix4 md, Matrix4 mi);
Poly   *prim_uv_decomp(Prim *p, Real level);
Vector3 prim_texc(Prim *p, Real u, Real v);
Vector3 prim_du(Prim *p, Real u, Real v);
Vector3 prim_dv(Prim *p, Real u, Real v);
Matrix4 prim_local(Prim *p);
int prim_id(Prim *p);
void prim_write(Prim *p, FILE *fp);
void prim_draw(Prim *p, int axis);

#define PRIM_IN  1
#define PRIM_OUT -1
#define PRIM_ON  0

/*  Primitive Types */

#define SPHERE 16
#include "sphere.h"


#endif
