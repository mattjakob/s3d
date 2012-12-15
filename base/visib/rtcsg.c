#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "defs.h"
#include "csg.h"
#include "ray.h"
#include "rt.h"

#define RI_OUT 0
#define RI_IN  1

Inode *csg_intersect(CsgNode *n, Ray r)
{
  if (n->type == CSG_COMP)
    return csg_ray_combine(n->u.c.op
		       , csg_intersect(n->u.c.lft, r)
		       , csg_intersect(n->u.c.rgt, r));
  else
    return prim_intersect(n->u.p, r);
}

#define CSG_MERGE(S, A) { int ts = cs;\
  S = !S;\
  if ((cs = csg_op(op, as, bs)) != ts) {\
    if (op == '-' && !S) \
      A->n = v3_scale(-1., A->n); \
    c->next = A; c = A; A = A->next;\
  } else {\
    t = A; A = A->next; t->next = NULL; inode_free(t);\
  }\
}

Inode *csg_ray_combine(char op, Inode *a, Inode *b)
{
  Inode in = {NULL, 0, {0,0,0}, 0, NULL}; 
  Inode *t, *c = &in, *f = &in;
  int as = (a&&(!a->enter)), bs = (b&&(!b->enter)), cs = csg_op(op, as, bs);

  while (a || b) {
    if ((a && b && a->t < b->t) || (a && !b))
      CSG_MERGE(as, a)
    else
      CSG_MERGE(bs, b)
  }
  c->next = (Inode *)0;
  return f->next;
}

int csg_op(char op, int l, int r)
{
  switch (op) {
  case '+': return l | r;
  case '*': return l & r;
  case '-': return l & (!r);
  }
}

