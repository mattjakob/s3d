#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "image.h"
#include "defs.h"
#include "geom.h"
#include "stack.h"
#include "view.h"
#include "poly.h"
#include "prim.h"
#include "hier.h"
#include "lang.h"
#include "clip.h"
#include "raster.h"
#include "shade.h"
#include "color.h"
#include "zbuf.h"
#include "obj.h"
#include "scene.h"
#include "radiosity.h"


typedef struct RadData {
  int n;
  Poly **pl;
  Color *e;
  Color *rho;
} RadData;


RadData *make_rad_data(Object *ol);

void init_sdl(void);
void init_render(void);
void pix_paint(Vector3 v,int n,int lv,Real lt,int rv,Real rt,Real st,void *c);
Poly *plist_refine(Poly *p, Real s, int maxrec);

