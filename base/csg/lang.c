#include "csg.h"


Val csg_prim_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  switch (pass) {
  case T_EXEC:
    v.type = V_CSG_NODE;
    if (p != NULL && p->val.type == V_PRIM)
      v.u.v = csg_prim(p->val.u.v);
    else
      error("(csg_op) syntax error");
    break;
  }
  return v;
}

Val csg_union_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};

  switch (pass) {
  case T_EXEC:
    if ((p != NULL && p->val.type == V_CSG_NODE)
	&& (p->next != NULL && p->next->val.type == V_CSG_NODE)) {
      v.type = V_CSG_NODE;
      v.u.v = csg_link('+', p->val.u.v, p->next->val.u.v);
    } else error("(csg_op) syntax error");
    break;
  }
  return v;
}

Val csg_inter_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  switch (pass) {
  case T_EXEC:
    if ((p != NULL && p->val.type == V_CSG_NODE)
	&& (p->next != NULL && p->next->val.type == V_CSG_NODE)) {
      v.type = V_CSG_NODE;
      v.u.v = csg_link('*', p->val.u.v, p->next->val.u.v);
    } else error("(csg_op) syntax error");
    break;
  }
  return v;
}

Val csg_diff_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  switch (pass) {
  case T_EXEC:
    if ((p != NULL && p->val.type == V_CSG_NODE)
	&& (p->next != NULL && p->next->val.type == V_CSG_NODE)) {
      v.type = V_CSG_NODE;
      v.u.v = csg_link('-', p->val.u.v, p->next->val.u.v);
    } else error("(csg_op) syntax error");
    break;
  }
  return v;
}


