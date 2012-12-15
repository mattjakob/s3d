/*
* mv.c
* multiple views
* Luiz Henrique de Figueiredo
* 08 Jan 93
*/

#include <stdlib.h>
#include "gp.h"
#include "mv.h"

static int	nv;			/* number of views */
static Box*	w;			/* windows */
static Box*	v;			/* viewports */
static int	current;

int mvopen(int n)
{
 if (n<=0) return 0;
 v=(Box*) emalloc(n*sizeof(Box)); if (v==0) return 0;
 w=(Box*) emalloc(n*sizeof(Box)); if (w==0) return 0;
 nv=n;
 current=0;
 for (n=0; n<nv; n++) {
   w[n].xu =  w[n].yu = 1.0;
   mvwindow(n,0.0,1.0,0.0,1.0);
   mvviewport(n,0.0,1.0,0.0,1.0);
 }
 return 1;
}

void mvclose(void)
{
 efree(w);
 efree(v);
}

void mvwindow(int n, real xmin, real xmax, real ymin, real ymax)
{
 if (n<0 || n>=nv) return;
 w[n].xmin=xmin;
 w[n].xmax=xmax;
 w[n].ymin=ymin;
 w[n].ymax=ymax;
}

void mvviewport(int n, real xmin, real xmax, real ymin, real ymax)
{
 if (n<0 || n>=nv) return;
 v[n].xmin=xmin;
 v[n].xmax=xmax;
 v[n].ymin=ymin;
 v[n].ymax=ymax;
}

void mvframe(void)
{
 int n = current;
 gpline(w[n].xmin,w[n].ymin,w[n].xmax,w[n].ymin);
 gpline(w[n].xmax,w[n].ymin,w[n].xmax,w[n].ymax);
 gpline(w[n].xmax,w[n].ymax,w[n].xmin,w[n].ymax);
 gpline(w[n].xmin,w[n].ymax,w[n].xmin,w[n].ymin);
}

void mvclear(int c)
{
 int old=gpcolor(c);
 int n=current;
 gpbox(w[n].xmin,w[n].xmax,w[n].ymin,w[n].ymax);
 gpcolor(old);
}

int mvact(int n)
{
 int old=current;
 if (n<0 || n>=nv) return old;
 gpwindow(w[n].xmin,w[n].xmax,w[n].ymin,w[n].ymax);
 gpviewport(v[n].xmin,v[n].xmax,v[n].ymin,v[n].ymax);
 current=n;
 return old;
}

void mvdiv(int nx, int ny, real xvmin, real xvmax, real yvmin, real yvmax)
{
 int i,n;
 real dx=(xvmax-xvmin)/nx;
 real dy=(yvmax-yvmin)/ny;
 for (n=0,i=0; i<ny; i++)
 {
  int j;
  real ymax=yvmax-i*dy;
  real ymin=ymax-dy;
  for (j=0; j<nx; j++,n++) {
   real xmin=xvmin+j*dx;
   real xmax=xmin+dx;
   mvviewport(n,xmin,xmax,ymin,ymax);
  }
 }
}

void mvmake(int nx, int ny)
{
 real x,y;
 if (nx>ny) {
  x=1.0;
  y=((real)ny)/nx;
 } else {
  x=((real)nx)/ny;
  y=1.0;
 }
 mvdiv(nx,ny,0.0,x,0.0,y);
 gpviewport(0.0,x,0.0,y);
}

char* mvevent(int wait, real* x, real* y, int* view)
{
 int n; real gx,gy, tx,ty;
 char* r=gpevent(wait,&gx,&gy);
 if (r==NULL) return r;
 gpview(&gx,&gy); tx=gx; ty=gy;
 gpwindow(0.0,1.0,0.0,1.0);
 gpviewport(0.0,1.0,0.0,1.0);
 gpunview(&gx,&gy);
 *view=-1;
 for (n=0; n<nv; n++) {
  if (gx>=v[n].xmin && gx<=v[n].xmax && gy>=v[n].ymin && gy<=v[n].ymax) {
   int old=mvact(n);
   gpunview(&tx,&ty);
   *x=tx;
   *y=ty;
   *view=n;
   mvact(old);
   break;
  }
 }
 return r;
}
