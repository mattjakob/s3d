#include "plot.h"

static Scene *s;
static Matrix4 mclip, mdpy;
static int bflag = TRUE;

void plot_init(char *name, Scene *scn, int bf)
{
  Real ar;
  s = scn; bflag = bf;
  gpopen(name, s->img->w, s->img->h);
  gpwindow(0, s->img->w, 0, s->img->h);
  gpviewport(0., 1., 0., 1.);
  gpclear(0);
  gprgb(1,0.,0.,0.);
  plot_init_render();
}

void plot_close(void)
{
  gpclose(1);
  exit(0);
}

void plot_newscene(Scene *scn)
{
  s = scn;
  plot_init_render();
}

void plot_showbuffer(int delay)
{
  gpswapbuffers();
  gpwait(delay);
}

void plot_poly(Poly *p)
{
  int i;
  gpcolor(2);
  gpbegin('p');
  for (i = 0; i < p->n; i++)
    gppoint(p->v[i].x, p->v[i].y);
  gpend();
  gpflush();
}

void plot_plist(Poly *pl)
{
  Poly *p;
  for (p = pl; p != NULL; p = p->next) 
    plot_render_poly(p);
}

void plot_csg(CsgNode *t)
{
  switch(t->type) {
  case CSG_PRIM:
    plot_prim(t->u.p);
    break;
  case CSG_COMP:
    plot_csg(t->u.c.lft);
    plot_csg(t->u.c.rgt);
    break;
  }
  gpflush();
}

void plot_prim(Prim *prm)
{
  Poly *l, *p;
  for (p = l = prim_uv_decomp(prm, 0.5); p != NULL; p = p->next)
    plot_render_poly(prim_polys(prm, p));
  plist_free(l);
}

Poly *prim_polys(Prim *prm, Poly *p)
{
  int i;
  for (i = 0; i < p->n; i++)
    p->v[i] = prim_point(prm, p->v[i].x, p->v[i].y);
  return p;
}

void plot_render_poly(Poly *p)
{
  if (bflag && is_backfacing(p, v3_sub(poly_centr(p), s->view->center)))
    return;
  if (poly_clip(VIEW_ZMIN(s->view), poly_transform(p, mclip), 0, 0))
    plot_poly(poly_homoxform(p, mdpy));
}

void plot_init_render(void)
{
  mclip = m4_m4prod(s->view->C, s->view->V);
  mdpy = m4_m4prod(s->view->S, s->view->P);
}  

