#include "lang.h"
#include "stack.h"
#include "sdltypes.h"
#include "prim.h"
#include "csg.h"
#include "poly.h"
#include "obj.h"

#define MAX_STK_DEPTH 32

static Stack4 *stk = NULL;

static void transform_objects(Pval *pl);
static Object *collect_objects(Pval *pl);

Val group_parse(int pass, Pval *pl)
{
  Val v = {V_NULL, 0};	
  switch (pass) {
  case T_PREP:
    if (stk == NULL)
      stk = s4_initstack(MAX_STK_DEPTH);
    s4_push(stk);
    break;
  case T_EXEC:
    transform_objects(pl);
    s4_pop(stk);
    v.u.v = collect_objects(pl);
    v.type = V_GROUP;
    break;
  default: break;
  }
  return v;
}


Val translate_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  if (pass == T_EXEC) {
    if (p->val.type == V_PVL)
      s4_translate(stk, pvl_to_v3(p->val.u.v));
    else
      error("(translate) wrong argument");
  }
  return v;
} 

Val scale_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  if (pass == T_EXEC) {
    if (p->val.type == V_PVL)
      s4_scale(stk, pvl_to_v3(p->val.u.v));
    else
      error("(scale) wrong argument");
  }
  return v;
}

Val rotate_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  if (pass == T_EXEC) {
    if (strcmp(p->name, "x") == 0 && p->val.type == V_NUM )
      s4_rotate(stk, 'x', p->val.u.d);
    else if (strcmp(p->name, "y") == 0 && p->val.type == V_NUM )
      s4_rotate(stk, 'y', p->val.u.d);
    else if (strcmp(p->name, "z") == 0 && p->val.type == V_NUM )
      s4_rotate(stk, 'z', p->val.u.d);
    else
      error("(rotate) wrong argument");
  }
  return v;
}

static void transform_objects(Pval *pl)
{
  Pval *p;
  for (p = pl; p != NULL; p = p->next)
    if (p->val.type == V_OBJECT)
      obj_transform(p->val.u.v, s4_getmat(stk), s4_getimat(stk));
}


static Object *collect_objects(Pval *pl)
{
  Pval *p; Object *olist = NULL;
  for (p = pl; p != NULL; p = p->next) {
    if (p->val.type == V_OBJECT)
      olist = obj_insert(olist, p->val.u.v);
    else if (p->val.type == V_GROUP)
      olist = obj_list_insert(olist, p->val.u.v);
  }
  return olist;
}
