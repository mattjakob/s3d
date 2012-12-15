#include "main.h"

static Scene *s;
static RContext *rc;
static Matrix4 mclip, mdpy;
static Color bgcolor = {0.1, 0.1, 0.1};


main(int argc, char **argv)
{
  Color c; int u, v;
  Ray r; Inode *l;

  init_sdl();
  s = scene_read();
  init_render();

  for (v = s->view->sc.ll.y; v < s->view->sc.ur.y; v += 1) {
    for (u = s->view->sc.ll.x; u < s->view->sc.ur.x; u += 1) {
      r = ray_unit(ray_transform(ray_view(u, v), mclip));
      if ((l = ray_intersect(s->objs, r)) != NULL)
        c = point_shade(ray_point(r, l->t), l->n, s->view->center, rc, l->m);
      else
        c = bgcolor;
      inode_free(l);
      img_putc(s->img, u, v, col_dpymap(c));
    }
  }
  img_write(s->img,"stdout",0);
  exit(0);
}

Ray ray_view(int u, int v)
{
  Vector4 w = v4_m4mult(v4_make(u, v, s->view->sc.ur.z, 1), mdpy);
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
  lang_defun("csgobj", obj_parse);
  lang_defun("csg_union", csg_union_parse);
  lang_defun("csg_inter", csg_inter_parse);
  lang_defun("csg_diff", csg_diff_parse);
  lang_defun("csg_prim", csg_prim_parse);
  lang_defun("sphere", sphere_parse);
}
