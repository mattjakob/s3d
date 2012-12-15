%{
#include <math.h>
#include "csg.h"
#include "csg.tab.h"
%}
%option noyywrap

D   [0-9]
S   [-]
%%

[ \t\n] ;
{S}?{D}*"."{D}+   |
{S}?{D}+"."{D}*   |
{S}?{D}+              { csglval.dval = atof( csgtext ); return NUM;}
.                     { return csgtext[0]; }

%%
