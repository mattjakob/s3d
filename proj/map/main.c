#include "main.h"

static Scene *s;
static Object *o;
static Matrix4 mclip, mdpy;
static RContext *rc;

static TextureData *td;

int main(int argc, char **argv)
{
  Poly *l, *p, *q = poly_alloc(8);
  Hpoly *t = hpoly_alloc(8);
  int i = 0;

  init_sdl();
  s = scene_read();
  init_render();

  for (o = s->objs; o != NULL; o = o->next) {
    for (l = prim_uv_decomp(o->u.prim, 1.); l != NULL; l = l->next, plist_free(p)) {
      p = poly_transform(prim_polys(o->u.prim, l), mclip);
      if ((is_backfacing(p, v3_unit(v3_scale(-1, poly_centr(p)))))
	  || (poly_clip(VIEW_ZMIN(s->view), p, free, 1) == 0))
	continue;
      q->n = t->n = p->n;
      t = hpoly_polyxform(t, SL(p), mdpy);
      q = poly_wz_hpoly(q, WL(p), t);
      texture_wscale(WL(p), TL(p));
      scan_poly(q, texture_zpaint,
		  texture_set(td,WL(p),TL(p),PL(p),NL(p),DUL(p),DVL(p),rc,M(o)));
      
    }
  }
  img_write(s->img, "stdout", 0);
  exit(0);
}

void texture_zpaint(Vector3 v,int n,int lv,Real lt,int rv,Real rt,Real st,void *c)
{
  if (zbuf_store(v))
    texture_shadepaint(v, n, lv, lt, rv, rt, st, c);
}

void init_render(void)
{
  mclip = m4_m4prod(s->view->C, s->view->V);
  mdpy = m4_m4prod(s->view->S, s->view->P);

  zbuf_init(s->img->w, s->img->h);

  td = NEWSTRUCT(TextureData);
  rc_sset(rc = NEWSTRUCT(RContext), s->view, s->lights, s->img);
}


Poly *prim_polys(Prim *s, Poly *p)
{
  int i;
  Poly *l = plist_alloc(7, p->n);

  for (i = 0; i < p->n; i++) {
    PL(l)->v[i] = SL(l)->v[i] = WL(l)->v[i] = prim_point(s, p->v[i].x, p->v[i].y);
    TL(l)->v[i] = prim_texc(s, p->v[i].x, p->v[i].y);
    NL(l)->v[i] = prim_normal(s, p->v[i].x, p->v[i].y);
    DUL(l)->v[i] = v3_unit(prim_du(s, p->v[i].x, p->v[i].y));
    DVL(l)->v[i] = v3_unit(prim_dv(s, p->v[i].x, p->v[i].y));
  }
  TAIL(l) = NULL;
  return l;
}

void init_sdl(void)
{
  lang_defun("scene", scene_parse);
  lang_defun("view", view_parse);
  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
  lang_defun("primobj", obj_parse);
  lang_defun("sphere", sphere_parse);

  lang_defun("slideproj", slideproj_parse);
  lang_defun("shiny", shiny_parse);
  lang_defun("rough", rough_parse);
  lang_defun("textured", textured_parse);
  lang_defun("imagemap", imagemap_parse);
  lang_defun("chequer", chequer_parse);

}

