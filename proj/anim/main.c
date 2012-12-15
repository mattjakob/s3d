#include "main.h"
#include "SDL.h"


static Boolean bflag = TRUE;
static Real timeoff = 100;

int main(int argc, char **argv)
{
  Scene *s;

  get_args(argc, argv);
  init_sdl();
  s = scene_read();

  gpsetdoublebuffer(1);
  plot_init("anim", s, bflag);
  while (!time_done(timeoff)) {
    plot_scene(s);
    scene_free(s);
    s = scene_eval();
    time_incr(1);
  }
  gpwait(-1);
  plot_close();
}  

void plot_scene(Scene *s)
{
  Object *o;
  plot_newscene(s);
  for (o = s->objs; o != NULL; o = o->next) {
    switch (o->type) {
    case V_POLYLIST: plot_plist(o->u.pols); break;
    case V_CSG_NODE: plot_csg(o->u.tcsg); break;
    case V_PRIM: plot_prim(o->u.prim); break;
    }
  }
  plot_showbuffer(30);
  gpclear(0);
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

  lang_defun("group", group_parse);
  lang_defun("translate", translate_parse);
  lang_defun("scale", scale_parse);
  lang_defun("rotate", rotate_parse);

  lang_defun("arg", arg_parse);
  lang_defun("motor", motor_parse);
}

void get_args(int argc, char **argv)
{
  switch (argc) {
  case 3: bflag = atoi(argv[2]);
  case 2: timeoff =  atoi(argv[1]);
  }
}
