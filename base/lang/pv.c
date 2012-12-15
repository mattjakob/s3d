#include <stdio.h>
#include "defs.h"
#include "lang.h"


/*:
**	append pv in list
*/
Pval *pv_append(Pval *pvlist, Pval *pv)
{
  Pval *p = pvlist;
  if (p == NULL)
    return pv;
  while (p->next != NULL)
    p = p->next;
  p->next = pv;
  return pvlist;
}

/*:
**	make pval datum
*/
Pval *pv_make(char *name, Val v)
{
  Pval *pv = (Pval *)emalloc(sizeof(Pval));
  pv->name = name;
  pv->val = v;
  pv->next = (Pval *)0;
  return pv;
}

/*:
**	set value
*/
Val pv_value(int type, double num, char *str, Node *nl)
{
  Val v;
  switch (v.type = type) {
  case V_STR: v.u.s = str; break;
  case V_NUM: v.u.d = num; break;
  case V_NOD: v.u.n = nl; break;
  }
  return v;
}
