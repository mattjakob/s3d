#include "main.h"

static Scene *s;
static RContext *rc;
static Matrix4 mclip, mdpy;
static Color bgcolor = {0.1, 0.1, 0.12};


Vector3 sphere_inv_param(Vector3 p)
{
  Vector3 u;
  u.x = PI + atan2(p.y, p.x);
  u.y = PI/2.0 + acos(p.z / sqrt(SQR(p.x) + SQR(p.y) + SQR(p.z)));
  u.z = 0;
  return u;
}

Color point_tshade(Vector3 p, Vector3 n, Vector3 v, RContext *rc, Material *m, Prim *s)
{
  Vector3 t, du, dv, u;
  u = sphere_inv_param(p);
  t = prim_texc(s, u.x, u.y); 
  du = v3_unit(prim_du(s, u.x, u.y));
  dv = v3_unit(prim_dv(s, u.x, u.y));
  return (*m->luminance)(rc_tset(rc, v3_unit(v), p, n, t, du, dv, m));
}

main(int argc, char **argv)
{
  Prim *o;
  Color c; int u, v;
  Ray r; Inode *l;

  o = sphere_instance(&sphere_funcs);
  init_sdl();
  s = scene_read();
  init_render();

  for (v = s->view->sc.ll.y; v < s->view->sc.ur.y; v += 1) {
    for (u = s->view->sc.ll.x; u < s->view->sc.ur.x; u += 1) {
      r = ray_unit(ray_transform(ray_view(u, v), mclip));
      if ((l = ray_intersect(s->objs, r)) != NULL) 
        c = point_tshade(ray_point(r, l->t), l->n, s->view->center, rc, l->m, o);
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
  lang_defun("primobj", obj_parse);
  lang_defun("sphere", sphere_parse);

  lang_defun("slideproj", slideproj_parse);
  lang_defun("shiny", shiny_parse);
  lang_defun("rough", rough_parse);
  lang_defun("textured", textured_parse);
  lang_defun("imagemap", imagemap_parse);
  lang_defun("chequer", chequer_parse);

}

