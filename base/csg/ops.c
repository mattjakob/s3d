#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csg.h"


CsgNode *csg_link(int op, CsgNode *lft, CsgNode *rgt)
{
  CsgNode *n = NEWSTRUCT(CsgNode);
  n->type = CSG_COMP;
  n->u.c.op = op;
  n->u.c.lft = lft;
  n->u.c.rgt = rgt;
  return n;
}

CsgNode *csg_prim(Prim *p)
{
  CsgNode *n = NEWSTRUCT(CsgNode);
  n->type = CSG_PRIM;
  n->u.p = p;
  return n;
}


char *csg_opname(char c)
{
  switch (c) {
  case '+': return "csg_union";
  case '*': return "csg_inter";
  case '-': return "csg_diff";
  default: return "";
  }
}

void csg_transform(CsgNode *t, Matrix4 m, Matrix4 mi)
{
  switch(t->type) {
  case CSG_PRIM:
    prim_transform(t->u.p, m, mi);
    break;
  case CSG_COMP:
    csg_transform(t->u.c.lft, m, mi);
    csg_transform(t->u.c.rgt, m, mi);
    break;
  }
}

void csg_destroy(CsgNode *t)
{
  switch(t->type) {
  case CSG_PRIM:
    prim_destroy(t->u.p);
    break;
  case CSG_COMP:
    csg_destroy(t->u.c.lft);
    csg_destroy(t->u.c.rgt);
    efree(t);
    break;
  }
}

void csg_write(CsgNode *t, FILE *fd)
{
  switch(t->type) {
  case CSG_PRIM: {
    fprintf(fd, "csg_prim{ "); prim_write(t->u.p, fd); fprintf(fd, "}");
    break;}
  case CSG_COMP:
    fprintf(fd, "%s {\n", csg_opname(t->u.c.op));
    csg_write(t->u.c.lft, fd); fprintf(fd, ",\n"); csg_write(t->u.c.rgt, fd);
    fprintf(fd, "\n}");
    break;
  }
}
