#include "geom.h"

Vector3   v3_zero  = { 0.0, 0.0, 0.0 };
Vector3   v3_e1    = { 1.0, 0.0, 0.0 };
Vector3   v3_e2    = { 0.0, 1.0, 0.0 };
Vector3   v3_e3    = { 0.0, 0.0, 1.0 };

Vector3 v3_make(Real x, Real y, Real z)
{
  Vector3 v;
  v.x = x; v.y = y; v.z = z;
  return v;
}

Vector3 v3_scale(Real t, Vector3 v)
{
  v.x *= t; v.y *= t; v.z *= t;
  return v;
}

Vector3 v3_add(Vector3 a, Vector3 b)
{
  a.x += b.x; a.y += b.y; a.z += b.z;
  return a;
}

Vector3 v3_sub(Vector3 a, Vector3 b)
{
  a.x -= b.x; a.y -= b.y; a.z -= b.z;
  return a;
}

Vector3 v3_cross(Vector3 u, Vector3 v)
{
  Vector3 uxv;
  uxv.x =    u.y * v.z - v.y * u.z;
  uxv.y =  - u.x * v.z + v.x * u.z;
  uxv.z =    u.x * v.y - u.y * v.x;
  return uxv;
}

Vector3 v3_unit(Vector3 u)
{
  Real  length = v3_norm(u);
  if(fabs(length) < EPS)
    error("(g3_unit) zero norm\n");
  else
    return v3_scale(1.0/length, u);
}

Real v3_dot(Vector3 u, Vector3 v)
{
  return (u.x * v.x + u.y * v.y + u.z * v.z);
}

Real v3_sqrnorm(Vector3 v)
{
  return (v.x * v.x + v.y * v.y + v.z * v.z);
}

Real v3_norm(Vector3 v)
{
  return sqrt((Real)(v.x * v.x + v.y * v.y + v.z * v.z));
}

Vector3 v3_v4conv(Vector4 v)
{
  if (REL_EQ(v.w, 0.)) v.w = 1;
  return v3_make(v.x/v.w, v.y/v.w, v.z/v.w);
}

Vector4 v4_make(Real x, Real y, Real z, Real w)
{
  Vector4 v;
  v.x = x; v.y = y; v.z = z, v.w = w;
  return v;
}

Vector4 v4_v3conv(Vector3 v)
{
  return v4_make(v.x, v.y, v.z, 1.0);
}

Real v4_dot(u,v)
     Vector4 u, v;
{
  return (u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w);
}

Vector3 v3_m4mult(Vector3 v, Matrix4 m)
{
  Vector4 w = v4_v3conv(v);
  return v3_make(v4_dot(w, m.r1), v4_dot(w, m.r2), v4_dot(w, m.r3));
}

Vector3 v3_m3mult(Vector3 v, Matrix4 m)
{
  Vector4 w = v4_make(v.x, v.y, v.z, 0.0);
  return v3_make(v4_dot(w, m.r1), v4_dot(w, m.r2), v4_dot(w, m.r3));
}

Vector4 v4_m4mult(Vector4 w, Matrix4 m)
{
  return v4_make(v4_dot(w, m.r1)
               , v4_dot(w, m.r2)
               , v4_dot(w, m.r3)
               , v4_dot(w, m.r4));
}

Vector3 v3_lerp(Real t, Vector3 a, Vector3 b)
{
  return v3_add(v3_scale((1-t), a), v3_scale((t), b));
}

Vector3 v3_bilerp(Real t, Real lt, Vector3 l0, Vector3 l1,
                          Real rt, Vector3 r0, Vector3 r1)
{
  return v3_lerp(t, v3_lerp(lt, l0, l1), v3_lerp(rt, r0, r1));
}

Vector3 v3_mult(Vector3 a, Vector3 b)
{
  Vector3 c;
  c.x = a.x * b.x;  c.y = a.y * b.y;  c.z = a.z * b.z;
  return c;
}

Boolean b3_inside(Box3d b, Vector3 p)
{
  return (   p.x > b.ll.x && p.x < b.ur.x
          && p.y > b.ll.y && p.y < b.ur.y
          && p.z > b.ll.z && p.z < b.ur.z );
}


