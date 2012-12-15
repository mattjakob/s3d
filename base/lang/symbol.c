/*	symbol.c - symbol lookup	*/

#include <stdio.h>
#include "defs.h"
#include "lang.h"
#include "symbol.h"

static Symbol *symlist = (Symbol *)0;

/*:
**	lookup symbol
*/
Symbol *sym_lookup(char *s)
{
  Symbol *sp;
  for (sp = symlist; sp != (Symbol *)0; sp = sp->next) {
    if (strcmp(sp->name, s) == 0)
      return sp;
  }
  return (Symbol *)0;
}

/*:
**	install symbol
*/
Symbol *sym_install(char *s, int t, Val (*f)(int, Pval *))
{
  Symbol *sp = (Symbol *) emalloc(sizeof(Symbol));

  sp->name = (char *)emalloc(strlen(s) + 1);
  strcpy(sp->name, s);
  sp->token = t;
  sp->func = f;
  sp->next = symlist;
  return symlist = sp;
}

