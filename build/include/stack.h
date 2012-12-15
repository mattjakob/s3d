#ifndef STACK_H
#define STACK_H

#include "geom.h"

typedef struct Stack4 {
  int size;
  Matrix4 
    *mbot,
    *mtop,
    *ibot,
    *itop;
} Stack4;

Stack4 *s4_initstack(int size);
void s4_push(Stack4 *s);
void s4_pop(Stack4 *s);

void s4_translate(Stack4 *s, Vector3 t);
void s4_scale(Stack4 *s, Vector3 v);
void s4_rotate(Stack4 *s, char axis, Real angle);

Vector3 s4_v3xform(Stack4 *s, Vector3 v);
Vector3 s4_n3xform(Stack4 *s, Vector3 nv);

Matrix4 s4_getmat(Stack4 *s);
Matrix4 s4_getimat(Stack4 *s);
void s4_loadmat(Stack4 *s, Matrix4 *md, Matrix4 *im);
void s4_concmat(Stack4 *s, Matrix4 *md, Matrix4 *im);

#endif
