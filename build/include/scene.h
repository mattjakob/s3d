#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include "lang.h"
#include "obj.h"
#include "sdltypes.h"

typedef struct Scene {
  struct View   *view;
  struct Image  *img;
  struct Light  *lights;
  struct Object *objs;
} Scene; 


Val scene_parse(int c, Pval *pl);
Scene *scene_read(void);
Scene *scene_eval(void);
void scene_free(Scene *s);

#endif
