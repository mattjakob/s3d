%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csg.h"

static CsgNode *csgroot;
%}

%union {
  char    cval;
  double  dval;
  CsgNode *nval;
}

%token <dval> NUM
%type <cval> bop
%type <nval> prim_obj csg_obj

%%

csg_obj:  '(' csg_obj bop csg_obj ')'  {$$ = csgroot = csg_link($3, $2, $4);}
        | prim_obj
	;
bop:      '|'                          {$$ = '+';}
        | '&'                          {$$ = '*';}
        | '\\'                         {$$ = '-';}
        ;
prim_obj: 's' '{' NUM NUM NUM NUM '}' 
          {$$ = csg_prim(sphere_set(sphere_instance(&sphere_funcs), v3_make($3, $4, $5), $6));}
        ;
%%

int csgerror()
{
  fprintf(stderr, "(CSG): syntax error\n");
}

CsgNode *csg_parse()
{
  if (csgparse() == 0)
    return csgroot;
  else
    return NULL;
}
