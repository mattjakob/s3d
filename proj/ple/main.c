/*
* ple.c
* polygonal line editor
* Luiz Henrique de Figueiredo
* 28 May 93
*/

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "laux.h"
#include "geom.h"
#include "gp.h"
#include "cb.h"

#include "SDL.h"

#define	TOL	tol

typedef struct point	Point;

struct point {
 real	x,y; 
 Point*	next;
 Point*	prev;
};

void	redraw		(int clear);
void	delpoints	(void);
void	showpolygon	(void);
void	showspline	(void);
void	showpoints	(void);
void	addpoint	(real x, real y);
void	movepoint	(real x, real y);
void	delpoint	(real x, real y);
void	startmove	(real x, real y);
void	endmove		(real x, real y);
void	showchange	(Point* p, int c);
void	showpoint	(Point* p);
void	showside	(Point* p, Point *q);
Point*	findpoint	(real x, real y);
void    read_curve       (char *fname);

Callback 
 do_clear,
 do_polygon,
 do_quit,
 do_redraw,
 do_addpoint,
 do_startmove,
 do_endmove,
 do_delpoint,
 do_movepoint;

#define	X(p)		((p)->x)
#define	Y(p)		((p)->y)
#define	new(t)		((t*)emalloc(sizeof(t)))
#define	next(p)		((p)->next)
#define	prev(p)		((p)->prev)

static Point*		firstpoint=NULL;
static Point*		lastpoint=NULL;
static int		showingpolygon=1;
static int		showingpoints=1;
static real             xmin = 0, xmax = 1, ymin = 0, ymax = 1;
static real             aspect = 1, tol = 0.1;


int main(int argc, char* argv[])
{
 if (argc == 2)
   read_curve(argv[1]);
 gpopen("polygonal line editor", 512 * aspect, 512);
 gpwindow(xmin,xmax, ymin,ymax);
 
 gpmark(0,"B");				/* filled box mark */
 redraw(1);
 gpregister("kc",do_clear,0);
 gpregister("kp",do_polygon,0);
 gpregister("kq",do_quit,0);
 gpregister("kr",do_redraw,0);
 gpregister("k\f",do_redraw,0);
 gpregister("b1+",do_addpoint,0);
 gpregister("kd",do_delpoint,0);
 gpregister("b3+",do_startmove,0);
 gpregister("b3-",do_endmove,0);
 gpregister("m3+",do_movepoint,0);
 gpmainloop();
 gpclose(0);
}

void redraw(int clear)
{
 if (clear)
   gpclear(0);
 if (showingpolygon)
   showpolygon();
 showpoints();
 gpflush();
}

void delpoints(void)
{
 firstpoint=lastpoint=NULL;			/* lazy! */
}

Point* moving=NULL;

void addpoint(real x, real y)
{
 Point* p=new(Point);
 X(p)=x;
 Y(p)=y;
 next(p)=NULL;
 if (showingpoints) showpoint(p);
 if (firstpoint==NULL) {
  prev(p)=NULL;
  firstpoint=p;
 } else {
  prev(p)=lastpoint;   next(lastpoint)=p;
  if (showingpolygon) showside(lastpoint,p);
 }
 lastpoint=p;
}

void delpoint(real x, real y)
{
 Point* p=findpoint(x,y);
 if (p!=NULL) {
  if (prev(p)==NULL) firstpoint=next(p); else next(prev(p))=next(p);
  if (next(p)==NULL) lastpoint=prev(p);  else prev(next(p))=prev(p);
  redraw(1);
 }
}

void startmove(real x, real y)
{
 moving=findpoint(x,y);
 if (moving!=NULL) {
  x=X(moving); y=Y(moving);
  gpcolor(0);    gpplot(x,y); gpcolor(1);
  gpmark(0,"b"); gpplot(x,y);
 }
}

void movepoint(real x, real y)
{
 if (moving!=NULL) {
  showchange(moving,0);
  X(moving)=x; Y(moving)=y;
  showchange(moving,1);
 }
 else startmove(x,y);
}

void endmove(real x, real y)
{
 if (moving!=NULL) {
  gpmark(0,"B");
  redraw(0);
  moving=NULL;
 }
}

Point* findpoint(real x, real y)
{
 Point* p=firstpoint;
 for (p=firstpoint; p!=NULL; p=next(p)) {
  if ((fabs(X(p)-x)+fabs(Y(p)-y))<TOL) break;
 }
 return p;
}

void showpoints(void)
{
 Point* p;
 for (p=firstpoint; p!=NULL; p=next(p))
  showpoint(p);
 gpflush();
}

void showpolygon(void)
{
 Point* p;
 for (p=firstpoint; p!=NULL; p=next(p))
  showside(p,next(p));
 gpflush();
}

void showpoint(Point* p)
{
 gpplot(X(p),Y(p));
}

void showside(Point* p, Point *q)
{
 if (p!=NULL && q!=NULL) gpline(X(p),Y(p),X(q),Y(q));
}

void showchange(Point* p, int c)
{
 gpcolor(c);
 showpoint(p);
 if (showingpolygon) {
  showside(prev(p),p);
  showside(p,next(p));
 }
 gpflush();
}

int do_clear(char* e, real x, real y, void* p)
{
 delpoints();
 redraw(1);
 return 0;
}

int do_polygon(char* e, real x, real y, void* p)
{
 showingpolygon=!showingpolygon;
 redraw(1);
 return 0;
}

int do_quit(char* e, real x, real y, void* p)
{
 return 1;
}

int do_redraw(char* e, real x, real y, void* p)
{
 redraw(1);
 return 0;
}

int do_addpoint(char* e, real x, real y, void* p)
{
 addpoint(x,y);
 gpflush();
 return 0;
}

int do_startmove(char* e, real x, real y, void* p)
{
 startmove(x,y);
 gpflush();
 return 0;
}

int do_endmove(char* e, real x, real y, void* p)
{
 endmove(x,y);
 gpflush();
 return 0;
}

int do_delpoint(char* e, real x, real y, void* p)
{
 delpoint(x,y);
 gpflush();
 return 0;
}

int do_movepoint(char* e, real x, real y, void* p)
{
 movepoint(x,y);
 gpflush();
 return 0;
}

void read_curve(char *fname)
{
  real x, y, z, m; int first = 1;
  FILE* fp = fopen(fname, "r+");

  if (fp == NULL) return;
  showingpoints = showingpolygon = 0;
  while (fscanf(fp, "%lf %lf %lf\n" ,&x,&y,&z) != EOF) {
    addpoint(x, y);
    if (first) {
      xmin = xmax = x;
      ymin = ymax = y;
      first = 0;
    }
    if (x < xmin) xmin = x;
    if (y < ymin) ymin = y;
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;
  }
  m = MAX((xmax - xmin), (ymax - ymin));
  aspect = (xmax - xmin) / (ymax - ymin);
  xmin -= m * 0.1;
  xmax += m * 0.1;
  ymin -= m * 0.1;
  ymax += m * 0.1;
  
  tol = m * 0.1;

  showingpoints = showingpolygon = 1;
}

