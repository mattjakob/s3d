#ifndef RAY_H
#define RAY_H

#include "defs.h"
#include "geom.h"

#define RAY_EPS 1e-7


typedef struct Ray {
  Vector3 o, d;
} Ray;

Ray ray_make(Vector3 o, Vector3 d);
Ray ray_transform(Ray r, Matrix4 m);
Ray ray_unit(Ray r);
Vector3 ray_point(Ray r, Real t);


typedef struct Inode {
  struct Inode    *next;
  double          t;
  Vector3         n;
  int             enter;
  struct Material *m;
} Inode;

Inode *inode_alloc(Real t, Vector3 n, int enter);
void inode_free(Inode *l);

#endif

