#ifndef RTLIB_H
#define RTLIB_H

#include "geom.h"
#include "ray.h"
#include "prim.h"
#include "poly.h"
#include "csg.h"
#include "obj.h"
#include "rtcsg.h"


Inode *ray_intersect(Object *olist, Ray r);

#endif
