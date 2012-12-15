#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "gp.h"
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
#include "scene.h"
#include "obj.h"
#include "zsort.h"


void init_sdl(void);
void init_render(void);

void z_store(Poly *l);

Poly *prim_polys(Prim *s, Poly *p);

#define S(I) (((Zdatum *)(I->d))->l)
#define P(I) (((Zdatum *)(I->d))->l->next)
#define N(I) (((Zdatum *)(I->d))->l->next->next)

#define M(I) (((Zdatum *)(I->d))->o->mat)

#define SL(L) (l)
#define PL(L) (l->next)
#define NL(L) (l->next->next)

