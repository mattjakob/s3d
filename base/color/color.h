#ifndef COLOR_H
#define COLOR_H

#include "geom.h"

typedef Vector3 Color;

#define RED(c) (c.x)
#define GRN(c) (c.y)
#define BLU(c) (c.z)

#define c_make(r,g,b) v3_make(r,g,b)
#define c_add(a, b)   v3_add(a,b)
#define c_sub(a, b)   v3_sub(a,b)
#define c_scale(a, b) v3_scale(a, b)
#define c_sqrnorm(a)  v3_sqrnorm(a)

#define c_mult(a, b)  v3_mult(a, b)

#define C_WHITE c_make(1,1,1)
#define C_BLACK c_make(0,0,0)


Color rgb_to_cmy(Color c);
Color cmy_to_rgb(Color c);
Color rgb_to_yiq(Color c);
Color yiq_to_rgb(Color c);

Real rgb_to_y(Color c);

Color rgb_to_hsv(Real r, Real g, Real b);
Color hsv_to_rgb(Real h, Real s, Real v);

int rgb_to_index(Color c, int nr, int ng, int nb);
Color index_to_rgb(int k, int nr, int ng, int nb);

#endif
