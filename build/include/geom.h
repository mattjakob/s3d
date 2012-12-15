#ifndef GEOLIB_H
#define GEOLIB_H

#include "defs.h"

typedef struct Vector3 {
  Real x,y,z;
} Vector3;

typedef struct Vector4 {
  Real x,y,z,w;
} Vector4;

typedef struct Matrix4 {
  Vector4 r1, r2, r3, r4;
} Matrix4;

typedef struct Box3d {
  Vector3 ll, ur;
} Box3d;


Vector3 v3_make(Real x, Real y, Real z);
Vector3 v3_scale(Real t, Vector3 v);
Vector3 v3_add(Vector3 a, Vector3 b);
Vector3 v3_sub(Vector3 a, Vector3 b);
Vector3 v3_cross(Vector3 u, Vector3 v);
Vector3 v3_unit(Vector3 u);
Real v3_dot(Vector3 u, Vector3 v);
Real v3_norm(Vector3 v);
Real v3_sqrnorm(Vector3 v);

Vector4 v4_make(Real x, Real y, Real z, Real w);
Real v4_dot(Vector4 u, Vector4 v);

Vector3 v3_v4conv(Vector4 w);
Vector4 v4_v3conv(Vector3 v);

Vector3 v3_m4mult(Vector3 v, Matrix4 m);
Vector3 v3_m3mult(Vector3 v, Matrix4 m);
Vector4 v4_m4mult(Vector4 w, Matrix4 m);

Matrix4 m4_ident();
Matrix4 m4_translate(Real tx, Real ty, Real tz);
Matrix4 m4_scale(Real sx, Real sy, Real sz);
Matrix4 m4_rotate(char axis, Real angle);
Matrix4 m4_transpose(Matrix4 m);
Matrix4 m4_m4prod(Matrix4 a, Matrix4 b);

Vector3 v3_mult(Vector3 a, Vector3 b);
Vector3 v3_lerp(Real t, Vector3 a, Vector3 b);
Vector3 v3_bilerp(Real t, Real lt, Vector3 l0, Vector3 l1,
                          Real rt, Vector3 r0, Vector3 r1);


Boolean b3_inside(Box3d b, Vector3 p);

#endif

