#include "ortho.h"


void ortho_init(int xmin, int xmax, int ymin, int ymax)
{
  int i; char label[]="0";

  gpopen("plot ortho", 512, 512);
  mvopen(4);
  mvdiv(2,2,0,1,0,1);
  for (i=0; i<4; i++) {
    mvwindow(i, xmin, xmax, ymin, ymax);
    mvact(i); mvframe();
    label[0] = ORTHO_CODE(i);
    gptext(.9*xmax,.9*ymax,label,"c");
  }
  gprgb(1,0.,0.,0.);
}

void ortho_close(void)
{
  gpswapbuffers();
  gpflush();
  mvclose();
  gpclose(1);
  exit(0);
}

void ortho_poly(Poly *p, int c)
{
  int i;
  gpcolor(2);
  gpbegin('p');
  for (i = 0; i < p->n; i++) {
    switch (c) {
    case 'x': gppoint(p->v[i].y, p->v[i].z); break;
    case 'y': gppoint(p->v[i].x, p->v[i].z); break;
    case 'z': gppoint(p->v[i].x, p->v[i].y); break;
    }
  }
  gpend();
  gpflush();
}

void ortho_plist(Poly *pl, int i)
{
  Poly *p;
  mvact(i);
  for (p = pl; p != NULL; p = p->next) 
    ortho_poly(p, ORTHO_CODE(i));
}

void ortho_csg(CsgNode *t, int i)
{
  switch(t->type) {
  case CSG_PRIM:
    ortho_prim(t->u.p, i);
    break;
  case CSG_COMP:
    ortho_csg(t->u.c.lft, i);
    ortho_csg(t->u.c.rgt, i);
    break;
  }
}

void ortho_prim(Prim *prm, int i)
{
  mvact(i);
  // prim_draw(prm, ORTHO_CODE(i));
  ortho_plot_bbox(prim_bbox(prm), ORTHO_CODE(i));
}

void ortho_plot_bbox(Box3d b, int axis)
{

  switch (axis) {
  case 'z':
    gpline(b.ll.x, b.ll.y, b.ll.x, b.ur.y);
    gpline(b.ll.x, b.ur.y, b.ur.x, b.ur.y);
    gpline(b.ur.x, b.ur.y, b.ur.x, b.ll.y);
    gpline(b.ur.x, b.ll.y, b.ll.x, b.ll.y);
    break;
  case 'y':
    gpline(b.ll.x, b.ll.z, b.ll.x, b.ur.z);
    gpline(b.ll.x, b.ur.z, b.ur.x, b.ur.z);
    gpline(b.ur.x, b.ur.z, b.ur.x, b.ll.z);
    gpline(b.ur.x, b.ll.z, b.ll.x, b.ll.z);
    break;
  case 'x':
    gpline(b.ll.z, b.ll.y, b.ll.z, b.ur.y);
    gpline(b.ll.z, b.ur.y, b.ur.z, b.ur.y);
    gpline(b.ur.z, b.ur.y, b.ur.z, b.ll.y);
    gpline(b.ur.z, b.ll.y, b.ll.z, b.ll.y);
    break;
  default:
    warning("(plot bbox) invalid projection");
  }
  gpflush();
}
