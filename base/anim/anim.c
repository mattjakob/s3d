#include <stdio.h>
#include <stdlib.h>
#include "lang.h"
#include "anim.h"

Val motor_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  switch (pass) {
  case T_EXEC:
    if (p != NULL && p->val.type == V_NUM)
      v.u.d = time_get() * p->val.u.d;
    else
      fprintf(stderr, "error: motor parse\n");
    v.type = V_NUM;
    break;
  }
  return v;
}

