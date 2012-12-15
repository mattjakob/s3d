#ifndef RADIOSITY_H
#define RADIOSITY_H

#include "defs.h"
#include "geom.h"
#include "poly.h"
#include "color.h"
#include "shade.h"

void radiosity_set(Real e, int iter, int vis);
Color *radiosity_prog(int n, Poly **p, Color *e, Color *rho);

#endif


