/*
* md.c
* move/draw metaphor for gp
* Luiz Henrique de Figueiredo
* 02 Feb 91
*/

#include "gp.h"

static real cx=0.0;
static real cy=0.0;

void gpwhere(real* x, real* y)
{
 *x = cx;
 *y = cy;
}

void gpmoveto(real x, real y)
{
 cx = x;
 cy = y;
}

void gpmoveby(real dx, real dy)
{
 cx += dx;
 cy += dy;
}

void gpdrawto(real x, real y)
{
 gpline(cx,cy,x,y);
 cx = x;
 cy = y;
}

void gpdrawby(real dx, real dy)
{
 gpline(cx,cy,cx+dx,cy+dy);
 cx += dx;
 cy += dy;
}
