#ifndef SYMBOL_H
#define SYMBOL_H
#include "string.h"

/*	symbol.h - symbol table defs	*/

typedef struct Symbol {
  char		*name;
  int		token;
  Val          (*func)(int, Pval *);
  struct Symbol	*next; 
} Symbol;

Symbol *sym_lookup(char *s);
Symbol *sym_install(char *s, int t, Val (*f)(int, Pval *));

#endif
