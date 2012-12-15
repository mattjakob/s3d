#include "main.h"

static Scene *s;
static Object *o;
static Matrix4 mclip, mdpy;
static RContext *rc;

static TextureData *td;
static List *z = NULL;

int main(int argc, char **argv)
{
  Poly *l, *p, *q = poly_alloc(3);
  Hpoly *t = hpoly_alloc(3);
  Item *i;

  init_sdl();
  s = scene_read();
  init_render();

  for (o = s->objs; o != NULL; o = o->next) {
    for (l = prim_uv_decomp(o->u.prim, 1.); l != NULL; l = l->next) {
      p = poly_transform(prim_polys(o->u.prim, l), mclip);
      if (!is_backfacing(p, v3_unit(v3_scale(-1, poly_centr(p)))))
	hither_clip(0, p, z_store, plist_free);
    }
  }
  z = z_sort(z);

  for (i = z->head; i != NULL; i = i->next) {
    t = hpoly_polyxform(t, S(i), mdpy);
    q = poly_wz_hpoly(q, W(i), t);
    texture_wscale(W(i), T(i));
    scan_spoly3(q, 2, texture_shadepaint,
             texture_set(td,W(i),T(i),P(i),N(i),DU(i),DV(i),rc,M(i)));
  }
  img_write(s->img, "stdout", 0);
  exit(0);
}

void init_render(void)
{
  mclip = m4_m4prod(s->view->C, s->view->V);
  mdpy = m4_m4prod(s->view->S, s->view->P);

  z = new_list();
  td = NEWSTRUCT(TextureData);
  rc_sset(rc = NEWSTRUCT(RContext), s->view, s->lights, s->img);
}

void z_store(Poly *l)
{
  Zdatum *d = NEWSTRUCT(Zdatum);
  d->zmax = MIN(l->v[0].z, MIN(l->v[1].z, l->v[2].z));
  d->l = l;
  d->o = o;
  append_item(z, new_item(d));
}


Poly *prim_polys(Prim *s, Poly *p)
{
  int i;
  Poly *l = plist_alloc(7, p->n);

  for (i = 0; i < p->n; i++) {
    PL(l)->v[i] = SL(l)->v[i] = prim_point(s, p->v[i].x, p->v[i].y);
    NL(l)->v[i] = prim_normal(s, p->v[i].x, p->v[i].y);
    TL(l)->v[i] = prim_texc(s, p->v[i].x, p->v[i].y);
    DUL(l)->v[i] = v3_unit(prim_du(s, p->v[i].x, p->v[i].y));
    DVL(l)->v[i] = v3_unit(prim_dv(s, p->v[i].x, p->v[i].y));
  }
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

