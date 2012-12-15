%{
#include <stdio.h>
#include <math.h>
#include "lang.h"
#include "symbol.h"

extern int yylex();
extern int yyerror();

static Node *root;

%}

%union {
  char	  ival;
  double  dval;
  char	 *sval;
  Pval	 *pval;
  Val     vval;
  Node	 *nval;
  Val    (*fval)(int, Pval *);
}

%token <sval> STRING NAME
%token <dval> NUMBER
%token <fval> CLASS

%type <nval> node input
%type <pval> pvlist pv
%type <vval> val

%%
input:	  /* empty */           { $$ = root = NULL;}
	| input node   ';'      { $$ = root = $2;}
	| input error  ';'      { yyerrok; $$ = root = NULL;}
	;
node:	  CLASS '{' pvlist '}'	{ $$ = t_node($1, $3); }
        | '{' pvlist '}'	{ $$ = t_node(t_pvl, $2); }
	;
pvlist:   /* empty */		{ $$ = (Pval *)0;}
	| pvlist ','  		{ $$ = $1;}
	| pvlist pv	 	{ $$ = pv_append($1, $2);}
	;
pv:	  NAME '=' val     	{ $$ = pv_make($1, $3);}
	| val     		{ $$ = pv_make(NULL, $1);}
	;
val:      NUMBER                { $$ = pv_value(V_NUM, $1, NULL, NULL);}
        | '-' NUMBER            { $$ = pv_value(V_NUM, - $2, NULL, NULL);}
        | STRING                { $$ = pv_value(V_STR, 0., $1, NULL);}
        | node                  { $$ = pv_value(V_NOD, 0., NULL, $1);}
        ;
%%

int yyerror()
{
  extern int lineno;
  return fprintf(stderr,"lang: syntax error in , near line %d\n", lineno);
}


void lang_defun(char *name, Val (*func)(int, Pval *))
{
  if (sym_lookup(name))
    fprintf(stderr,"lang: symbol %s already defined\n", name);
  else
    sym_install(name, CLASS, func);
}


Val lang_eval(void)
{
  return (root != NULL)? t_eval(root) : pv_value(V_NUM, 0, NULL, NULL);
}


Val lang_nd_eval(void)
{
  return (root != NULL)? t_nd_eval(root) : pv_value(V_NUM, 0, NULL, NULL);
}


Node *lang_ptree(void)
{
  return root;
}
