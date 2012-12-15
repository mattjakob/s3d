#include "ray.h"

Ray ray_make(Vector3 o, Vector3 d)
{
  Ray r;
  r.o = o; r.d = d;
  return r;
}

Ray ray_transform(Ray r, Matrix4 m)
{
  r.o = v3_m4mult(r.o, m);
  r.d = v3_m3mult(r.d, m);
  return r;
}

Ray ray_unit(Ray r)
{
  r.d = v3_unit(r.d);
  return r;
}

Vector3 ray_point(Ray r, Real t)
{
  return v3_add(r.o, v3_scale(t, r.d));
}

