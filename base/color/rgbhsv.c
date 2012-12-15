#include "color.h"


Color rgb_to_hsv(Real r, Real g, Real b)
{
  Real v, x, f;
  int i;

  x = MIN(r, MIN(g, b));
  v = MAX(r, MAX(g, b));
  if (v == x)
    return v3_make(UNDEFINED, 0, v);
  f = (r == x) ? g - b : ((g == x) ? b - r : r - g);
  i = (r == x) ? 3 : ((g == x) ? 5 : 1);
  return c_make(i - f /(v - x), (v - x)/v, v);

}

Color hsv_to_rgb(Real h, Real s, Real v)
{
  Real m, n, f;
  int i;

  if(h == UNDEFINED)
    return c_make(v, v, v);
  i = floor(h);
  f = h - i;
  if(EVEN(i))
    f = 1 - f;
  m = v * (1 - s);
  n = v * (1 - s * f);
  switch (i) {
  case 6:
  case 0: return c_make(v, n, m);
  case 1: return c_make(n, v, m);
  case 2: return c_make(m, v, n);
  case 3: return c_make(m, n, v);
  case 4: return c_make(n, m, v);
  case 5: return c_make(v, m, n);
  }
}
