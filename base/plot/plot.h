#ifndef _PLOT_H
#define _PLOT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "gp.h"
#include "defs.h"
#include "geom.h"
#include "poly.h"
#include "prim.h"
#include "csg.h"
#include "view.h"
#include "clip.h"
#include "scene.h"
#include "image.h"


void plot_init(char *name, Scene *s, int bflag);
void plot_close(void);
void plot_showbuffer(int delay);

void plot_init_render(void);
void plot_render_poly(Poly *p);

void plot_poly(Poly *p);
void plot_plist(Poly *pl);

void plot_prim(Prim *prm);
Poly *prim_polys(Prim *prm, Poly *p);

void plot_csg(CsgNode *t);


#endif
