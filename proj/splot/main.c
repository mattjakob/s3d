#include "main.h"
#include "plot.h"
#include "SDL.h"

static Boolean bflag = TRUE;

int main(int argc, char **argv)
{
  Scene *s; Object *o;

  get_args(argc, argv);
  init_sdl();
  s = scene_read();

  plot_init("plot scene", s, bflag);
  for (o = s->objs; o != NULL; o = o->next) {
    switch (o->type) {
    case V_POLYLIST: plot_plist(o->u.pols); break;
    case V_CSG_NODE: plot_csg(o->u.tcsg); break;
    case V_PRIM: plot_prim(o->u.prim); break;
    }
  }
  plot_showbuffer(0);
  plot_close();
}


void init_sdl(void)
{
  lang_defun("scene", scene_parse);
  lang_defun("view", view_parse);
  lang_defun("polyobj", obj_parse);
  lang_defun("trilist", trilist_parse);

  lang_defun("primobj", obj_parse);
  lang_defun("sphere", sphere_parse);

  lang_defun("csgobj", obj_parse);
  lang_defun("csg_union", csg_union_parse);
  lang_defun("csg_inter", csg_inter_parse);
  lang_defun("csg_diff", csg_diff_parse);
  lang_defun("csg_prim", csg_prim_parse);

  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
}

void get_args(int argc, char **argv)
{
  switch (argc) {
  case 2:
    bflag =  atoi(argv[1]);
  }
}
