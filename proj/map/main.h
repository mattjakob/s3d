#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "gp.h"
#include "image.h"
#include "color.h"
#include "defs.h"
#include "geom.h"
#include "stack.h"
#include "view.h"
#include "poly.h"
#include "hpoly.h"
#include "prim.h"
#include "hier.h"
#include "lang.h"
#include "clip.h"
#include "raster.h"
#include "shade.h"
#include "map.h"
#include "scene.h"
#include "obj.h"
#include "zsort.h"

void init_sdl(void);
void init_render(void);
Poly *prim_polys(Prim *s, Poly *p);

#define M(o) (o->mat)

#define SL(l) (l)
#define WL(l) (l->next)
#define TL(l) (l->next->next)
#define PL(l) (l->next->next->next)
#define NL(l) (l->next->next->next->next)
#define DUL(l) (l->next->next->next->next->next)
#define DVL(l) (l->next->next->next->next->next->next)
#define TAIL(l) (l->next->next->next->next->next->next->next)

void texture_zpaint(Vector3 v,int n,int lv,Real lt,int rv,Real rt,Real st,void *c);



