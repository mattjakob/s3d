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
void z_store(Poly *l);
Poly *prim_polys(Prim *s, Poly *p);

#define S(I) (((Zdatum *)(I->d))->l)
#define W(I) (((Zdatum *)(I->d))->l->next)
#define T(I) (((Zdatum *)(I->d))->l->next->next)
#define P(I) (((Zdatum *)(I->d))->l->next->next->next)
#define N(I) (((Zdatum *)(I->d))->l->next->next->next->next)
#define DU(I) (((Zdatum *)(I->d))->l->next->next->next->next->next)
#define DV(I) (((Zdatum *)(I->d))->l->next->next->next->next->next->next)

#define M(I) (((Zdatum *)(I->d))->o->mat)

#define SL(L) (l)
#define WL(L) (l->next)
#define TL(L) (l->next->next)
#define PL(L) (l->next->next->next)
#define NL(L) (l->next->next->next->next)
#define DUL(L) (l->next->next->next->next->next)
#define DVL(L) (l->next->next->next->next->next->next)


