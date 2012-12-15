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
#include "csg.h"
#include "hier.h"
#include "lang.h"
#include "clip.h"
#include "raster.h"
#include "shade.h"
#include "zbuf.h"
#include "scene.h"
#include "gp.h"
#include "plot.h"
#include "anim.h"


void get_args(int argc, char **argv);
void init_sdl(void);
void plot_scene(Scene *s);
