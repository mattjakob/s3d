#include "lang.h"
#include "sdltypes.h"
#include "obj.h"

#ifdef SHADE_LIB
#include "shade.h"
#define SET_MAT_DEFAULT(o)     {(o)->mat = mat_default();}
#else
#define SET_MAT_DEFAULT(o) {;}
#endif


void obj_transform(Object *o, Matrix4 m, Matrix4 mi)
{
  switch (o->type) {
  case V_PRIM: prim_transform(o->u.prim, m, mi); break;
  case V_CSG_NODE: csg_transform(o->u.tcsg, m, mi); break;
  case V_POLYLIST: plist_transform(o->u.pols, m); break;
  }
}


Object *obj_new(int type, void *v)
{
  Object *o = NEWSTRUCT(Object);
  o->next = NULL;
  SET_MAT_DEFAULT(o);
  switch (o->type = type) {
  case V_CSG_NODE: o->u.tcsg = v; break;
  case V_PRIM: o->u.prim = v; break;
  case V_POLYLIST:   o->u.pols = v; break;
  default: error("(newobj) wrong type");
  }
  return o;
}

void obj_free(Object *o)
{
  switch (o->type) {
  case V_PRIM: prim_destroy(o->u.prim); break;
  case V_CSG_NODE: csg_destroy(o->u.tcsg); break;
  case V_POLYLIST: plist_free(o->u.pols); break;
  }
  efree(o->mat->tinfo); 
  efree(o->mat);
  efree(o);
}

Object *obj_insert(Object *olist, Object *o)
{
  o->next = olist;
  return o;
}

Object *obj_list_insert(Object *olist, Object *l)
{
  Object *t, *o = l;
  while (o != NULL) {
    t = o; o = o->next;
    olist = obj_insert(olist, t);
  }
  return olist;
}

void obj_list_free(Object *ol)
{
  Object *t, *o = ol;
  while (o != NULL) {
    t = o; o = o->next;
    obj_free(t);
  }
}

Val obj_parse(int c, Pval *pl)
{
  Val v = {V_NULL, 0};
  if (c == T_EXEC) { Pval *p;
    Object *o = NEWSTRUCT(Object);
    o->mat = NULL;
    for (p = pl; p !=NULL; p = p->next) {
      if (p->name == NULL) {
      	error("(object) syntax error");
      } else if (strcmp(p->name, "material") == 0 && p->val.type == V_MATERIAL) {
        o->mat = p->val.u.v;
      } else if (strcmp(p->name, "shape") == 0 && p->val.type == V_PRIM) {
        o->type = V_PRIM; o->u.prim = p->val.u.v;
      } else if (strcmp(p->name, "shape") == 0 && p->val.type == V_POLYLIST) {
        o->type = V_POLYLIST; o->u.pols = p->val.u.v;
      } else if (strcmp(p->name, "shape") == 0 && p->val.type == V_CSG_NODE) {
        o->type = V_CSG_NODE; o->u.tcsg = p->val.u.v;
      } else error("(object) syntax error"); 
    }
    if (o->mat == NULL)
      SET_MAT_DEFAULT(o);
    v.type = V_OBJECT;
    v.u.v = o;
  }
  return v;
}
