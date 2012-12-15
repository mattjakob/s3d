/*
* gp.c
* a simple 2d graphics package
* Luiz Henrique de Figueiredo (lhf@visgraf.impa.br) - 28 Apr 93
* Modified by Luiz Velho (lvelho@impa.br) - 16/09/98
*/

#include <stdlib.h>
#include <stdio.h>
#include "gp.h"

static struct {
 Box w, v, d;
 real ax ,bx, ay, by;
} gp = {
 {0.0, 1.0, 0.0, 1.0, 1.0, 1.0},
 {0.0, 1.0, 0.0, 1.0, 1.0, 1.0},
 {0.0, 1.0, 0.0, 1.0, 1.0, 1.0},
  1.0, 0.0, 1.0, 0.0,
};

static void calculate_aspect (void)
{
  if (gp.d.xu > gp.d.yu) {
    gp.d.xu /= gp.d.yu;
    gp.d.yu =  1.0;
  } else {
    gp.d.yu /= gp.d.xu;
    gp.d.xu  = 1.0;
  }
}

real gpopen(char* name, int width, int height)
{
 real aspect;
 gp.d=*dvopen(name, width, height);
 calculate_aspect();
 gpwindow(0.0,1.0,0.0,1.0);
 gpviewport(0.0,1.0,0.0,1.0);
 gprgb(0,1.,1.,1.);
 gprgb(1,0.,0.,0.);
 gpcolor(1);
 return (gp.d.xu/gp.d.yu);
}

real gpwindow(real xmin, real xmax, real ymin, real ymax)
{
  gp.w.xmin=xmin;
  gp.w.xmax=xmax;
  gp.w.ymin=ymin;
  gp.w.ymax=ymax;
  gpmake();
  dvwindow(xmin, xmax, ymin, ymax);
  return (xmax-xmin)/(ymax-ymin);
}

real gpviewport(real xmin, real xmax, real ymin, real ymax)
{
  gp.v.xmin=xmin;
  gp.v.xmax=xmax;
  gp.v.ymin=ymin;
  gp.v.ymax=ymax;
  gpmake();
  dvviewport(xmin, xmax, ymin, ymax);
  return (xmax-xmin)/(ymax-ymin);
}

void gpmake(void)
{
 real Ax=(gp.d.xmax-gp.d.xmin);
 real Ay=(gp.d.ymax-gp.d.ymin);
 gp.ax = (gp.v.xmax-gp.v.xmin)/(gp.w.xmax-gp.w.xmin);   /* map wc to ndc */
 gp.ay = (gp.v.ymax-gp.v.ymin)/(gp.w.ymax-gp.w.ymin);
 gp.bx =  gp.v.xmin-gp.ax*gp.w.xmin;
 gp.by =  gp.v.ymin-gp.ay*gp.w.ymin;
 gp.ax = Ax*gp.ax;                                      /* map ndc to dc */
 gp.ay = Ay*gp.ay;
 gp.bx = Ax*gp.bx+gp.d.xmin;
 gp.by = Ay*gp.by+gp.d.ymin;
}

void gpview(real* x, real* y)
{
 *x=gp.ax*(*x)+gp.bx;
 *y=gp.ay*(*y)+gp.by;
}

void gpunview(real* x, real* y)
{
 *x=(*x-gp.bx)/gp.ax;
 *y=(*y-gp.by)/gp.ay;
}

char* gpevent(int wait, real* x, real* y)
{
  int ix,iy;
  char* r=dvevent(wait,&ix,&iy);
  *x=ix; *y=iy;
  gpunview(x,y);
  return r;
}

