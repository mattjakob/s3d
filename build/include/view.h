#ifndef VIEWLIB_H
#define VIEWLIB_H

#include "lang.h"

#define PERSPECTIVE  1
#define ORTHOGRAPHIC 2


typedef struct UVpoint {
  Real u,v;
} UVpoint;


typedef struct View {

  Vector3  center;	/* center of projection */
  Vector3  normal;	/* view plane normal vector */
  Vector3  up;		/* view up vector */

  Real	   dist;	/* view plane distance from viewpoint*/
  Real	   front;	/* front plane dist. from viewpoint */
  Real	   back;	/* back plane dist. from viewpoint */

  UVpoint  c;		/* relative to view plane center */
  UVpoint  s;		/* window u,v half sizes */

  Box3d    sc;          /* current, in pix space */

  int      type;        /* projection type */

  Matrix4  V, Vinv;     /* view xform and inverse */
  Matrix4  C, Cinv;     /* clip space xform and inverse */

  Matrix4  P, Pinv;     /* perspective xforms and inverse */
  Matrix4  S, Sinv;     /* device xform and inverse */

} View;


#define VIEW_ZMIN(v)   ((v)->front / (v)->back)
#define VIEW_ASPECT(v) ((v)->s.u / (v)->s.v)
#define VIEW_FIELD(v)  (2.0 * atan((v)->s.u / (v)->dist))
#define VIEW_PIX_AR(v) (VIEW_ASPECT(v) * ((v)->sc.ur.y - (v)->sc.ll.y + 1) \
			               / ((v)->sc.ur.x - (v)->sc.ll.x + 1))

#define ROUNDOFF EPS

View* initview(void);
void lookat(View *v,Real vx, Real vy, Real vz, Real px, Real py, Real pz, 
	    Real ux, Real uy, Real uz);
void polarview(View *v, Real dist, Real azimuth, Real pich, Real roll);
void camera(View *v, Real rx, Real ry, Real rz, Real nx, Real ny, Real nz, Real ux, Real uy, Real uz, Real deye);
void perspective(View *v, Real fov, Real ar, Real near, Real far);
void orthographic(View *v, Real l, Real b, Real r, Real t, Real near, Real far);
void frustrum(View *v, Real l, Real b, Real r, Real t, Real near, Real far);
void viewport(View *v, Real l, Real b, Real w, Real h);

void setview(View *v);
View *getview(void);
void setviewpoint(Real x, Real y, Real z);
void setviewnormal(Real x, Real y, Real z);
void setviewup(Real x, Real y, Real z);
void setviewdistance(Real d);
void setviewdepth(Real front, Real back);
void setwindow(Real cu, Real cv, Real su, Real sv);
void setprojection(int type);
void setviewport(Real l, Real b, Real r, Real t, Real n, Real f);
void setviewdefaults(void);

void makeviewV(void);
void makeviewC(void);
void makeviewO(void);
void makeviewP(void);
void makeviewS(void);
void makeviewVi(void);
void makeviewCi(void);
void makeviewOi(void);
void makeviewPi(void);
void makeviewSi(void);

Val view_parse(int pass, Pval *pl);

#endif
