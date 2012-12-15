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
#include "ray.h"
#include "csg.h"
#include "rt.h"
#include "map.h"

#include "scene.h"


void init_sdl(void);
Ray ray_view(int u, int v);
void init_render(void);





