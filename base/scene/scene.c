#include "scene.h"

#ifdef VIEW_LIB
#include "image.h"
#include "view.h"
#endif

#ifdef SHADE_LIB
#include "shade.h"
#endif

static struct View *view = NULL;
static struct Image *img = NULL;
static struct Light *lights = NULL;
static struct Object *objs = NULL;

#define LIST_INSERT(L, I, TYPE) {struct TYPE *tt = I; tt->next = L; L = tt; }


static void collect_items(Pval *pl)
{
  Pval *p = pl;
  while (p != NULL) {
    if (p->name && strcmp(p->name,"object") == 0 && p->val.type == V_OBJECT) 
      objs = obj_insert(objs, p->val.u.v);
    else if (p->name && strcmp(p->name,"object") == 0 && p->val.type == V_GROUP)
      objs = obj_list_insert(objs, p->val.u.v);
#ifdef VIEW_LIB
    else if (p->name && strcmp(p->name,"camera") == 0 && p->val.type == V_CAMERA)
      view = p->val.u.v;
#endif
#ifdef SHADE_LIB
    else if (p->name && strcmp(p->name,"light") == 0 && p->val.type == V_LIGHT)
      LIST_INSERT(lights, p->val.u.v, Light)
#endif
    p = p->next;
  }
}


Val scene_parse(int c, Pval *pl)
{
  Val v = {V_NULL, 0};
  
  if (c == T_EXEC) {
    Scene *s = NEWSTRUCT(Scene);
    view = NULL; img = NULL; lights = NULL; objs = NULL;

    collect_items(pl);
#ifdef VIEW_LIB
    s->view = view;
    s->img = img;
#endif
#ifdef SHADE_LIB
    s->lights = lights;
#endif
    s->objs = objs;
    v.type = V_SCENE;
    v.u.v = s;
  }
  return v;
}


Scene *scene_read(void)
{
  if (lang_parse() == 0)
    return scene_eval();
  else
    error("(scene read)");
}


Scene *scene_eval(void)
{
  Scene *s;
  Val v = lang_nd_eval();
  if (v.type != V_SCENE)
    error("(scene eval)");
  else
    s =  v.u.v;
#ifdef VIEW_LIB
  if (s->view == NULL)
    s->view = initview();
  if (s->img == NULL)
    s->img = img_init(IMG_TRUECOL, s->view->sc.ur.x, s->view->sc.ur.y);
#endif
#ifdef SHADE_LIB
  if (lights == NULL)
    s->lights = light_ambient(.5);
#endif
  return s;
}

void scene_free(Scene *s)
{
  if (s->objs)
    obj_list_free(s->objs);
#ifdef VIEW_LIB
  if (s->view)
    efree(s->view);
  if (s->img)
    img_free(s->img);
#endif
#ifdef SHADE_LIB
  if (s->lights) {
    Light *t, *l = s->lights;
    while (l != NULL) {
      t = l; l = l->next;
      efree(t->tinfo); efree(t);
    }
  }
#endif
  efree(s);
}


