#ifndef _ORTHO_H
#define _ORTHO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "gp.h"
#include "mv.h"
#include "defs.h"
#include "geom.h"
#include "poly.h"
#include "prim.h"
#include "csg.h"

void ortho_init(int xmin, int xmax, int ymin, int ymax);
void ortho_close(void);
void ortho_poly(Poly *p, int i);
void ortho_plist(Poly *pl, int i);

void ortho_prim(Prim *prm, int i);
void ortho_csg(CsgNode *t, int i);

void ortho_plot_bbox(Box3d b, int axis);

#define ORTHO_CODE(i) ((i==1)? 'y' : ((i==2)? 'x' : (i==3)? 'z' : 'c'))

#endif
