#include "main.h"

static Scene *s;
static RContext *rc;
static Matrix4 mclip, mdpy;

int main(int argc, char **argv)
{
  Object *o;  Poly *p;  Color c;

  init_sdl();
  s = scene_read();
  init_render();

  for (o = s->objs; o != NULL; o = o->next) {
    for (p = o->u.pols; p != NULL; p = p->next) {
      if (is_backfacing(p, v3_sub(poly_centr(p), s->view->center)))
	continue;
      c = flat_shade(p, s->view->center, rc, o->mat);
      if (poly_clip(VIEW_ZMIN(s->view), poly_transform(p, mclip), 0, 0))
	scan_poly(poly_homoxform(p, mdpy), pix_paint, &c);
    }
  }
  img_write(s->img, "stdout", 0);
  exit(0);
}

void pix_paint(Vector3 v,int n,int lv,Real lt,int rv,Real rt,Real st,void *c)
{
  if (zbuf_store(v))
    img_putc(s->img, v.x, v.y, col_dpymap(*((Color *)(c))));
}

void init_render(void)
{
  mclip = m4_m4prod(s->view->C, s->view->V);
  mdpy = m4_m4prod(s->view->S, s->view->P);

  zbuf_init(s->img->w, s->img->h);

  rc_sset(rc = NEWSTRUCT(RContext), s->view, s->lights, s->img);
}  


void init_sdl(void)
{
  lang_defun("scene", scene_parse);
  lang_defun("view", view_parse);
  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
  lang_defun("polyobj", obj_parse);
  lang_defun("trilist", trilist_parse);
}

