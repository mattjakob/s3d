#ifndef RTCSGLIB_H
#define RTCSGLIB_H

#include "geom.h"
#include "ray.h"
#include "prim.h"
#include "csg.h"
#include "obj.h"

Inode *csg_intersect(CsgNode *n, Ray r);
Inode *csg_ray_combine(char op, Inode *a, Inode *b);
int csg_op(char op, int l, int r);

#endif
