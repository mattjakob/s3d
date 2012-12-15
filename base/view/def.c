/*	def.c - viewing definitions procedures	*/

#include <stdio.h>
#include <math.h>
#include "defs.h"
#include "geom.h"
#include "view.h"


View* initview(void)
{
  setview(NEWSTRUCT(View));
  setviewdefaults();
  makeviewV();
  makeviewC();
  makeviewP();
  makeviewS();
  return getview();
}


void lookat(View *v, Real vx, Real vy, Real vz,
	    Real px, Real py, Real pz, Real ux, Real uy, Real uz)
{
  setview(v);
  setviewpoint(vx, vy, vz);
  setviewnormal(px - vx ,py - vy, pz - vz);
  setviewup(ux, uy, uz);
  makeviewV();
}


void polarview(View *v, Real dist, Real azimuth, Real pich, Real roll)
{
  setview(v);
  setviewnormal(sin(azimuth)*cos(pich),	cos(azimuth)*cos(pich), sin(pich));
  setviewpoint(-dist * v->normal.x,-dist * v->normal.y, -dist * v->normal.z );
  if (fabs(v->normal.x) < ROUNDOFF && fabs(v->normal.y) < ROUNDOFF)
    setviewup(sin(roll)*v->normal.z, -cos(roll)*v->normal.z,0.0);
  else
    setviewup(sin(roll)*v->normal.y, -sin(roll)*v->normal.x,
	      cos(roll)*hypot(v->normal.x,v->normal.y));
  makeviewV();
}


void camera(View *v, Real rx, Real ry, Real rz, Real nx, Real ny, Real nz
     , Real ux, Real uy, Real uz, Real deye)
{
  setview(v);
  setviewup(ux, uy, uz);
  setviewnormal(nx, ny, nz);
  setviewpoint(rx - (v->normal.x*deye),
	       ry - (v->normal.y*deye),
	       rz - (v->normal.z*deye));
  makeviewV();
}


void perspective(View *v, Real fov, Real ar, Real near, Real far)
{
  setview(v);
  setprojection(PERSPECTIVE);
  setviewdistance(near);
  setviewdepth(near,far);
  if (ar < ROUNDOFF)
    error("illegal aspect ratio");
  setwindow(0, 0, tan(fov/2) * near, (tan(fov/2) * near)/ar);
  makeviewC();
  makeviewP();
}


void orthographic(View *v, Real l, Real b, Real r, Real t, Real near, Real far)
{
  setview(v);
  setprojection(ORTHOGRAPHIC);
  setviewdistance(near);
  setviewdepth(near,far);
  setwindow((l+r)/2, (b+t)/2, (r-l)/2, (t-b)/2);
  makeviewC();
  makeviewO();
}


void frustrum(View *v, Real l, Real b, Real r, Real t, Real near, Real far)
{
  setview(v);
  setprojection(PERSPECTIVE);
  setviewdistance(near);
  setviewdepth(near,far);
  setwindow((l+r)/2, (b+t)/2, (r-l)/2, (t-b)/2);
  makeviewC();
  makeviewP();
}


void viewport(View *v, Real l, Real b, Real w, Real h)
{
  setview(v);
  setviewport(l,b,l+w,b+h,-32767.,32767.);
  makeviewS();
}
