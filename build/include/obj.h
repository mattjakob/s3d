#ifndef OBJ_H
#define OBJ_H

#include "geom.h"
#include "lang.h"


typedef struct Object {
  struct Object   *next;
  struct Material *mat;
  int   type;
  union {
    struct Poly    *pols;
    struct Prim    *prim;
    struct CsgNode *tcsg;
  } u;
} Object;


void obj_transform(Object *o, Matrix4 m, Matrix4 mi);
Object *obj_new(int type, void *v);
void obj_free(Object *o);
Object *obj_insert(Object *olist, Object *o);
Object *obj_list_insert(Object *olist, Object *l);
void obj_list_free(Object *ol);
Val obj_parse(int c, Pval *pl);


#endif

