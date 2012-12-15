#include <stdio.h>

#ifdef __APPLE__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include "defs.h"
#include "lang.h"
#include "symbol.h"
#include "y.tab.h"


Val t_eval(Node *n)
{
  Pval *p;

  (*n->func)(T_PREP, n->plist);
  for (p = n->plist; p != NULL; p = p->next)
    if (p->val.type == V_NOD)
      p->val = t_eval(p->val.u.n);
  return (*n->func)(T_EXEC, n->plist);
}


Val t_nd_eval(Node *n)
{
  Val v; Pval *p, *qlist = NULL;

  (*n->func)(T_PREP, n->plist);
  for (p = n->plist; p != NULL; p = p->next)
    qlist = pv_append(qlist, pv_make(p->name,
                      (p->val.type == V_NOD)? t_nd_eval(p->val.u.n) : p->val));
  v = (*n->func)(T_EXEC, qlist);
  if (n->func != t_pvl) pvl_free(qlist);
  return v;
}


Node *t_node(Val (*f)(int, Pval *), Pval *p)
{
  Node *n = (Node *) emalloc(sizeof(Node));
  n->func = f;
  n->plist = p;
  return n;
}


Val t_pvl(int c, Pval *pvl)
{
  Val v;
  v.type = V_PVL;  v.u.v = pvl;
  return v;
}

