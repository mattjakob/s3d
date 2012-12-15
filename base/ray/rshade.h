#ifndef RAYSHADE_H
#define RAYSHADE_H

#include "geom.h"
#include "ray.h"
#include "shade.h"
#include "obj.h"


Color ray_shade(int level, Real w, Ray v, RContext *rc, Object *ol);

Vector3 reflect_dir(Vector3 d, Vector3 n);
Vector3 refract_dir(Vector3 d, Vector3 n, Real eta);
Real shadow(Light *l, Vector3 p, Object *ol);

#endif
