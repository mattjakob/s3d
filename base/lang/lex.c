/*   lex.c - lexical analizer */

#include <stdio.h>
#include <ctype.h>

#ifdef __APPLE__
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include "defs.h"
#include "lang.h"
#include "symbol.h"
#include "y.tab.h"

extern int yyparse();

int lineno = 0;

static FILE *fin = NULL;
static int c;


int yylex()
{
  Symbol *s;

  while ((c = getc(fin)) == ' ' || c == '\t')
    ;
  if (c == EOF)
    return 0;
  if (c == '.' || isdigit(c)) { double d;
    ungetc(c, fin);
    fscanf(fin, "%lf", &d);
    yylval.dval = d;
    return NUMBER;
  }
  if (c == '"') { char sbuf[320], *p;
    for (p = sbuf; (c = getc(fin)) != '"'; *p++ = c) {
      if (c == '\\') 
	c = ((c = getc(fin)) == '\n')? ' ' : c;
      if (c == '\n' || c == EOF) {
	fprintf(stderr,"missing quote, sbuf\n");
	break;
      }
      if (p >= sbuf + sizeof(sbuf) - 1) {
	fprintf(stderr,"sbuffer overflow\n");
	break;
      }
    }
    *p = '\0';
    yylval.sval = (char *)emalloc(strlen(sbuf) + 1);
    strcpy(yylval.sval, sbuf);
    return STRING;
  }
  if (isalpha(c)) { char sbuf[1024], *p = sbuf;
    do {
      if (p >= sbuf + sizeof(sbuf) - 1) {
	*p = '\0';
	fprintf(stderr,"name too long %s\n", sbuf);
      }
      *p++ = c;
    } while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_' ));
    ungetc(c, fin);
    *p = '\0';
    if ((s = sym_lookup(sbuf)) == (Symbol *)0)
      s = sym_install(sbuf, NAME, NULL);
    if (s->token == CLASS)
      yylval.fval = s->func;
    else
      yylval.sval = s->name;
    return s->token;
  }
  switch (c) {
  case '\\': if ((c = getc(fin)) != '\n')
               return c;
             else
               return yylex();
  case '\n': lineno++; return yylex();
  default:   return c;
  }
}

void lang_file(FILE *fd)
{
  fin = fd;
}

int lang_parse(void)
{
  if (fin == NULL) lang_file(stdin);
  return yyparse();
}
