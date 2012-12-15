#include <stdio.h>

#ifdef __APPLE__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include <string.h>
#include "lang.h"


void pvl_to_array(Pval *pvl, double *a, int n)
{
  int k = 0;  
  Pval *p = pvl;

  while (p != NULL && k < n) {
    a[k++] = (p->val.type == V_NUM) ? p->val.u.d : 0;
    p = p->next;
  }
}


Vector3 pvl_to_v3(Pval *pvl)
{
  double a[3] = {0, 0, 0};
  pvl_to_array(pvl, a, 3);
  return v3_make(a[0], a[1], a[2]);
}


Real pvl_get_num(Pval *pvl, char *name, Real defval)
{
  Pval *p;
  for (p = pvl; p != (Pval *)0; p = p->next)
    if (p->name && strcmp(p->name, name) == 0 && p->val.type == V_NUM)
      return p->val.u.d;
  return defval;
}


Vector3 pvl_get_v3(Pval *pvl, char *name, Vector3 defval)
{
  Pval *p;
  for (p = pvl; p != (Pval *)0; p = p->next)
    if (p->name && strcmp(p->name, name) == 0 && p->val.type == V_PVL)
      return pvl_to_v3((Pval *)(p->val.u.v));
  return defval;
}

void pvl_free(Pval *pvl)
{
  Pval *q, *p = pvl;
  while (p != NULL) {
    q = p;  p = p->next;
    if (q->val.type == V_PVL)
      pvl_free((Pval *)(q->val.u.v));
    efree(q);
  }
}

