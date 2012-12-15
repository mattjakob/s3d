/*
* cb.c
* callback manager
* Luiz Henrique de Figueiredo
* 08 Oct 92
*/

#include <string.h>
#include "defs.h"
#include "gp.h"
#include "cb.h"

typedef struct event	Event;

struct event {
 char* s;
 Callback* f;
 void* d;
 Event* next;
};

#define new(t)			( (t*) emalloc(sizeof(t)) )
#define	streq(x,y)		(strcmp(x,y)==0)
#define	S(_)			((_)->s)
#define	F(_)			((_)->f)
#define	D(_)			((_)->d)
#define	next(_)			((_)->next)
#define	foreachevent(e)		for (e=firstevent; e!=NULL; e=next(e))

static Event*	findevent	(char* s);
static Event*	matchevent	(char* s);
static int	match		(char *s, char *pat);

static Event*	firstevent=NULL;
static int	gp_wait=1;

void gpmainloop(void)
{
 for (;;) {
  real x,y;
  char* s=gpevent(gp_wait,&x,&y);
  Event*e=matchevent(s);
  if (e!=NULL && F(e)(s,x,y,D(e))) break;
 }
}

Callback* gpregister(char* s, Callback* f, void* d)
{
 Callback* old;
 Event* e=findevent(s);
 if (e==NULL) {
  static Event* lastevent=NULL;
  e=new(Event);				/* watch out for NULL! */
  S(e)=s;
  F(e)=NULL;
  next(e)=NULL;
  if (firstevent==NULL) firstevent=e; else next(lastevent)=e;
  lastevent=e;
 }
 old=F(e);
 F(e)=f;
 D(e)=d;
 if (s==NULL && f!=NULL) gp_wait=0;
 return old;
}

static Event* findevent(char* s)
{
 Event* e;
 foreachevent(e) {
  if (streq(S(e),s)) break;
 }
 return e;
}

static Event* matchevent(char* s)
{
 Event* e;
 foreachevent(e) {
  if (match(S(e),s)) break;
 }
 return e;
}

static int match(char *s, char *pat)
{
 for (; *s!=0; s++, pat++) {
  if (*s!=*pat) return 0;
 }
 return 1;
}
