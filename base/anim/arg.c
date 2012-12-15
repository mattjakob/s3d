#include "anim.h"

static int m_argc;
static char **m_argv;

void arg_init(int ac, char **av)
{
  m_argc = ac; m_argv = av;
}

double arg_get_dval(char *s, Real defval)
{
  int i;
  for (i = 1; i < m_argc; i++)
    if (m_argv[i][0] == '-' && strcmp(m_argv[i]+1, s) == 0 && i+1 < m_argc)
      return atof(m_argv[i+1]);
  return defval;  
}

Val arg_parse(int pass, Pval *p)
{
  Val v = {V_NULL, 0};
  switch (pass) {
  case T_EXEC:
    if (p != NULL && p->val.type == V_NUM)
      v.u.d = arg_get_dval(p->name, p->val.u.d);
    else
      fprintf(stderr, "error: arg parse %lx\n",p);
    v.type = V_NUM;
    break;
  }
  return v;
}
