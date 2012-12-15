#include "main.h"
#include "SDL.h"

static Scene *s;
static Real xmin = -1, ymin = -1, xmax = 1, ymax = 1; 

int main(int argc, char **argv)
{
  Object *o; int i;

  get_args(argc, argv);
  init_sdl();
  s = scene_read();

  ortho_init(xmin, xmax, ymin, ymax);

  for (o = s->objs; o != NULL; o = o->next) {
    for (i = 1; i < 4; i++) {
      switch (o->type) {
      case V_POLYLIST: ortho_plist(o->u.pols, i); break;
      case V_CSG_NODE: ortho_csg(o->u.tcsg, i); break;
      case V_PRIM: ortho_prim(o->u.prim, i); break;
      }
    }
  }
  ortho_close();
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

  lang_defun("group", group_parse);
  lang_defun("translate", translate_parse);
  lang_defun("scale", scale_parse);
  lang_defun("rotate", rotate_parse);

  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
}

void get_args(int argc, char **argv)
{
  if (argc == 3) {
    xmin = ymin = atof(argv[1]);
    xmax = ymax = atof(argv[2]);
  } else if (argc == 4) {
    xmin = atof(argv[1]); xmax = atof(argv[2]);
    ymin = atof(argv[3]); ymax = atof(argv[4]);
  }
}
