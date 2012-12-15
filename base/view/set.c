/*	view.c - viewing transformation procedures	*/

#include <stdio.h>
#include <math.h>
#include "defs.h"
#include "geom.h"
#include "view.h"


static	View *view;


void setview(View *v)
{
  view = v;
}

View *getview(void)
{
  return view;
}

void setviewpoint(Real x, Real y, Real z)
{
  view->center.x = x;
  view->center.y = y;
  view->center.z = z;
}

void setviewnormal(Real x, Real y, Real z)
{
  double d = sqrt(SQR(x)+SQR(y)+SQR(z));

  if (d < ROUNDOFF)
    error("invalid view plane normal");
  view->normal.x = x / d;
  view->normal.y = y / d;
  view->normal.z = z / d;
}

void setviewup(Real x, Real y, Real z)
{
  if (fabs(x) + fabs(y) + fabs(z) < ROUNDOFF)
    error("no view up direction");
  view->up.x = x;
  view->up.y = y;
  view->up.z = z;
}

void setviewdistance(Real d)
{
  if (fabs(d) < ROUNDOFF)
    error("invalid view distance");
  view->dist = d;
}

void setviewdepth(Real front, Real back)
{
  if (fabs(back - front) < ROUNDOFF || fabs(back) < ROUNDOFF)
    error("invalid viewdepth");
  view->front = front;
  view->back = back;
}

void setwindow(Real cu, Real cv, Real su, Real sv)
{
  if (fabs(su) < ROUNDOFF || fabs(sv) < ROUNDOFF)
    error("invalid window size");
  view->c.u = cu; view->c.v = cv;
  view->s.u = su; view->s.v = sv;
}

void setprojection(int type)
{
  if (type != PERSPECTIVE && type != ORTHOGRAPHIC)
    error("invalid projection type");
  view->type = type;
}

void setviewport(Real l, Real b, Real r, Real t, Real n, Real f)
{
  if(fabs(r-l) < ROUNDOFF || fabs(t-b) < ROUNDOFF)
    error("invalid viewport");
  view->sc.ll.x = l;  view->sc.ur.x = r;
  view->sc.ll.y = b;  view->sc.ur.y = t;
  view->sc.ll.z = n;  view->sc.ur.z = f;
}

void setviewdefaults(void)
{
  setviewpoint(0.0,-5.0,0.0);
  setviewnormal(0.0,1.0,0.0);
  setviewup(0.0,0.0,1.0);
  setviewdistance(1.0);
  setviewdepth(1.0,100000.0);
  setwindow(0.0,0.0,0.41421356,0.31066017);
  setprojection(PERSPECTIVE);
  setviewport(0.,0.,320.,240.,-32768.,32767.);
}


void makeviewV(void)
{
  Vector3 n,u,v,t;

  n = view->normal;
  v = v3_sub(view->up, v3_scale(v3_dot(view->up, n), n));
  if (v3_norm(v) < ROUNDOFF)
    error("view up parallel to view normal");
  v = v3_unit(v);
  u = v3_cross(n, v);
  t.x = v3_dot(view->center, u);
  t.y = v3_dot(view->center, v);
  t.z = v3_dot(view->center, n);

  view->V = m4_ident();
  view->V.r1.x =  u.x; view->V.r2.x =  v.x; view->V.r3.x =  n.x;
  view->V.r1.y =  u.y; view->V.r2.y =  v.y; view->V.r3.y =  n.y;
  view->V.r1.z =  u.z; view->V.r2.z =  v.z; view->V.r3.z =  n.z;
  view->V.r1.w = -t.x; view->V.r2.w = -t.y; view->V.r3.w = -t.z;

  makeviewVi();
}

void makeviewC(void)
{
  view->C = m4_ident();
  view->C.r1.x = view->dist / (view->s.u * view->back);
  view->C.r2.y = view->dist / (view->s.v * view->back);
  view->C.r3.z = 1 / view->back;
  view->C.r1.z = - view->c.u / (view->s.u * view->back);
  view->C.r2.z = - view->c.v / (view->s.v * view->back);
  makeviewCi();
}

void makeviewO(void)
{
  view->C = m4_ident();
  view->C.r1.x = 1 / view->s.u;
  view->C.r2.y = 1 / view->s.v;
  view->C.r3.z = 1 / (view->back - view->front);
  view->C.r1.w = - view->c.u / view->s.u;
  view->C.r2.w = - view->c.v / view->s.v;
  view->C.r3.w = - view->front / (view->back - view->front);
  view->P = m4_ident();
  makeviewOi();
}

void makeviewP(void)
{
  view->P = m4_ident();
  view->P.r3.z = view->back / (view->back - view->front);
  view->P.r3.w = -view->front / (view->back - view->front);
  view->P.r4.z = 1;
  view->P.r4.w = 0;
  makeviewPi();
}

void makeviewS(void)
{
  view->S = m4_ident();
  view->S.r1.x = (view->sc.ur.x - view->sc.ll.x) / 2;
  view->S.r2.y = (view->sc.ur.y - view->sc.ll.y) / 2;
  view->S.r3.z =  view->sc.ur.z - view->sc.ll.z;
  view->S.r1.w = (view->sc.ur.x + view->sc.ll.x +1) / 2;
  view->S.r2.w = (view->sc.ur.y + view->sc.ll.y +1) / 2;
  view->S.r3.w =  view->sc.ll.z + 0.5;
  makeviewSi();
}

void makeviewVi(void)
{
  Vector3 n,u,v,t;

  view->Vinv = m4_ident();
  n = view->normal;
  v = v3_sub(view->up, v3_scale(v3_dot(view->up, n), n));
  if (v3_norm(v) < ROUNDOFF)
    error("view up parallel to view normal");
  v = v3_unit(v);
  u = v3_cross(n, v);
  t = view->center;

  view->Vinv = m4_ident();
  view->Vinv.r1.x = u.x; view->Vinv.r2.x = u.y; view->Vinv.r3.x = u.z;
  view->Vinv.r1.y = v.x; view->Vinv.r2.y = v.y; view->Vinv.r3.y = v.z;
  view->Vinv.r1.z = n.x; view->Vinv.r2.z = n.y; view->Vinv.r3.z = n.z;
  view->Vinv.r1.w = t.x; view->Vinv.r2.w = t.y; view->Vinv.r3.w = t.z;
}

void makeviewCi(void)
{
  view->Cinv = m4_ident();
  view->Cinv.r1.x = (view->s.u * view->back) / view->dist;
  view->Cinv.r2.y = (view->s.v * view->back) / view->dist;
  view->Cinv.r3.z = view->back;
  view->Cinv.r1.z = (view->c.u * view->back) / view->dist;
  view->Cinv.r2.z = (view->c.v * view->back) / view->dist;
}

void makeviewOi(void)
{
  view->Cinv = m4_ident();
  view->Cinv.r1.x = view->s.u;
  view->Cinv.r2.y = view->s.v;
  view->Cinv.r3.z = (view->back - view->front);
  view->Cinv.r1.w = view->c.u;
  view->Cinv.r2.w = view->c.v;
  view->Cinv.r3.w = view->front;
  view->Pinv = m4_ident();
}

void makeviewPi(void)
{
  view->Pinv = m4_ident();
  view->Pinv.r3.z = 0;
  view->Pinv.r4.z = - (view->back - view->front) / view->front;
  view->Pinv.r4.w = view->back / view->front;
  view->Pinv.r3.w = 1;
  view->Pinv.r4.w = 0;
}

void makeviewSi(void)
{
  view->Sinv = m4_ident();
  view->Sinv.r1.x = 2 / (view->sc.ur.x - view->sc.ll.x);
  view->Sinv.r2.y = 2 / (view->sc.ur.y - view->sc.ll.y);
  view->Sinv.r3.z = 1 / (view->sc.ur.z - view->sc.ll.z);
  view->Sinv.r1.w = - (view->sc.ur.x + view->sc.ll.x +1) /
                    (view->sc.ur.x - view->sc.ll.x);
  view->Sinv.r2.w = - (view->sc.ur.y + view->sc.ll.y +1) / 
                    (view->sc.ur.y - view->sc.ll.y);
  view->Sinv.r3.w = - (view->sc.ll.z + 0.5) /
                    (view->sc.ur.z - view->sc.ll.z);
}

