#include "main.h"

static Scene *s;
static RContext *rc;
static Matrix4 mclip, mdpy;
static Color bgcolor = {0.0, 0.0, 0.0};


main(int argc, char **argv)
{
  Color c; int u, v;
  Ray r;

  init_sdl();
  s = scene_read();
  init_render();

  for (v = s->view->sc.ll.y; v < s->view->sc.ur.y; v += 1) {
    for (u = s->view->sc.ll.x; u < s->view->sc.ur.x; u += 1) {
      r = ray_unit(ray_transform(ray_view(u, v), mclip));
      c = ray_shade(0, 1., r, rc, s->objs);
      img_putc(s->img, u, v, col_dpymap(c));
    }
  }
  img_write(s->img,"stdout",0);
  exit(0);
}

Ray ray_view(int u, int v)
{
  Vector4 w = v4_m4mult(v4_make(u, v,s->view->sc.ur.z, 1), mdpy);
  return ray_make(v3_v4conv(v4_m4mult(v4_make(0, 0, 1, 0), mdpy)),
		  v3_make(w.x, w.y, w.z));
}

void init_render(void)
{
  mclip = m4_m4prod(s->view->Vinv, s->view->Cinv);
  mdpy = m4_m4prod(s->view->Pinv, s->view->Sinv);

  rc_sset(rc = NEWSTRUCT(RContext), s->view, s->lights, s->img);
}

void init_sdl(void)
{
  lang_defun("scene", scene_parse);
  lang_defun("view", view_parse);
  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
  lang_defun("primobj", obj_parse);
  lang_defun("sphere", sphere_parse);
  lang_defun("polyobj", obj_parse);
  lang_defun("trilist", trilist_parse);


  lang_defun("group", group_parse);
  lang_defun("translate", translate_parse);
  lang_defun("scale", scale_parse);
  lang_defun("rotate", rotate_parse);

}
