#ifndef POLY_H
#define POLY_H

#include "sdltypes.h"
#include "geom.h"
#include "ray.h"
#include "lang.h"

typedef struct Poly {
  struct Poly *next;
  int          n;
  Vector3     *v;
} Poly;

Poly *poly_alloc(int n);
Poly *poly_transform(Poly *p, Matrix4 m);
Poly *poly_homoxform(Poly *p, Matrix4 m);
Vector3 poly_normal(Poly *p);
Poly *poly_insert(Poly *pl, Poly *p);
int poly_copy(Poly *s, Poly *d);
Vector3 poly_centr(Poly *p);
Inode *poly_intersect(Poly *p, Vector4 plane, Ray r);

Poly *poly3_make(Vector3 v0, Vector3  v1, Vector3  v2);
int poly3_read(Poly *p, FILE* fp);
void poly3_write(Poly *p, FILE* fp);
Poly *poly3_decode(Pval *plist);
Vector4 poly3_plane(Poly *p);

void trilist_write(Poly *tlist, FILE* fp);
Val trilist_parse(int pass, Pval *plist);

int plist_lenght(Poly *l);
Poly *plist_alloc(int n, int m);
void plist_free(Poly *l);
Poly *plist_transform(Poly *l, Matrix4 m);

Real poly3_ray_inter(Poly *p, Vector4 plane, Ray r);
Real poly3_area(Poly *p);

#endif
