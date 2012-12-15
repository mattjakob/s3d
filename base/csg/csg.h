#ifndef CSG_H
#define CSG_H

#include "geom.h"
#include "prim.h"
#include "sdltypes.h"


#define CSG_PRIM   0
#define CSG_COMP   1

typedef struct CsgComp{        /* CSG Composite */
  char           op;           /* Boolean Operation + - * */
  struct CsgNode *lft, *rgt;   /* Pointer to Children */
} CsgComp;
  
typedef struct CsgNode {       /* CSG Tree Node */
  int    type;                 /* CSG_PRIM or CSG_COMP */
  union {
    struct CsgComp  c;          /* Composite */
    struct Prim    *p;          /* Primitive */
  } u;
} CsgNode;


CsgNode *csg_parse();
CsgNode *csg_prim(Prim *p);
CsgNode *csg_link(int op, CsgNode *lft, CsgNode *rgt);
void csg_destroy(CsgNode *t);

char *csg_opname(char c);
void csg_transform(CsgNode *t, Matrix4 m, Matrix4 mi);
void csg_write(CsgNode *t, FILE *fd);

Val csg_union_parse(int c, Pval *p);
Val csg_inter_parse(int c, Pval *p);
Val csg_diff_parse(int c, Pval *p);
Val csg_prim_parse(int c, Pval *p);

#endif
