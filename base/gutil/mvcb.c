/*
* mvcb.c
* callback manager for mv
* Luiz Henrique de Figueiredo
* 08 Jan 93
*/

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "gp.h"
#include "mv.h"

typedef struct event	Event;

struct event {
 int v;
 char* s;
 MvCallback* f;
 void* d;
 Event* next;
};

#define new(t)			( (t*) emalloc(sizeof(t)) )
#define	streq(x,y)		(strcmp(x,y)==0)
#define	V(_)			((_)->v)
#define	S(_)			((_)->s)
#define	F(_)			((_)->f)
#define	D(_)			((_)->d)
#define	next(_)			((_)->next)
#define	foreachevent(e)		for (e=firstevent; e!=NULL; e=next(e))

static Event*	findevent	(int v, char* s);
static Event*	matchevent	(int v, char* s);
static int	match		(char *s, char *pat);

static Event*	firstevent=NULL;
static int	gp_wait=1;

void mvmainloop(void)
{
 for (;;) {
  real x,y;
  int v;
  char* s=mvevent(gp_wait,&x,&y,&v);
  Event*e=matchevent(v,s);
  if (e!=NULL && F(e)(D(e),v,x,y,s))
    break;
 }
}

MvCallback* mvregister(int v, char* s, MvCallback* f, void* d)
{
 MvCallback* old;
 Event* e=findevent(v,s);
 if (e==NULL) {
  static Event* lastevent=NULL;
  e=new(Event);				/* watch out for NULL! */
  V(e)=v;
  S(e)=s;
  F(e)=NULL;
  next(e)=NULL;
  if (firstevent==NULL) firstevent=e; else next(lastevent)=e;
  lastevent=e;
 }
 old=F(e);
 F(e)=f;
 D(e)=d;
 if (s[0]=='i' && f!=NULL) gp_wait=0;
 return old;
}


static Event* findevent(int v, char* s)
{
 Event* e;
 foreachevent(e) {
  if (V(e)!=v) continue;
  if (s==NULL && S(e)==NULL) break;
  if (s==NULL || S(e)==NULL) continue;
  if (streq(S(e),s)) break;
 }
 return e;
}

static Event* matchevent(int v, char* s)
{
 Event* e;
 foreachevent(e) {
   if (V(e)<0 || V(e)==v)
     if (match(S(e),s)) break;
 }
 return e;
}

static int match(char *s, char *pat)
{
 if (s==NULL) return pat==NULL;
 if (pat==NULL) return s==NULL;
 for (; *s!=0; s++, pat++) {
  if (*s!=*pat) return 0;
 }
 return 1;
}

#if 0
mvreg(1,"b1+",displ,id1);	/* chama displ(id1) se botao 1 for press em v1*/
mvreg(2,"b1+",displ,id2);
mvreg(-1,"=q",exit,0);		/* chama exit(0) se key q em qq vista */
mvreg(3,"k",k,0);		/* chama k(0) se qq key em v3 */
mvreg(-1,NULL,work,p);		/* chama work(p) se nada acontece */
#endif
