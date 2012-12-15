#include <stdio.h>
#include "geom.h"
#include "poly.h"

#define FRT_0  0
#define FRT_1  1
#define BCK_0  2
#define BCK_1  3
#define LFT_0  4
#define LFT_1  5
#define RGT_0  6
#define RGT_1  7
#define BOT_0  8
#define BOT_1  9
#define TOP_0  10
#define TOP_1  11
#define NTRI   12


int main(int argc, char **argv)
{
  int i;
  Real x0, x1, y0, y1, z0, z1;
  Vector3 v1, v2, v3, v4, v5, v6, v7, v8;
  Poly *cube[NTRI], *plist = NULL;

  x0 = -100;  x1 = 100;
  y0 = -100;  y1 = 100;
  z0 = -100;  z1 = 100;

  v1 = v3_make(x0, y0, z0);
  v2 = v3_make(x1, y0, z0);
  v3 = v3_make(x1, y1, z0);
  v4 = v3_make(x0, y1, z0);
  v5 = v3_make(x0, y0, z1);
  v6 = v3_make(x1, y0, z1);
  v7 = v3_make(x1, y1, z1);
  v8 = v3_make(x0, y1, z1);


  cube[FRT_0] = poly3_make(v3, v1, v2);
  cube[FRT_1] = poly3_make(v1, v3, v4);
  cube[BCK_0] = poly3_make(v5, v7, v6);
  cube[BCK_1] = poly3_make(v7, v5, v8);
  cube[LFT_0] = poly3_make(v8, v1, v4);
  cube[LFT_1] = poly3_make(v1, v8, v5);
  cube[RGT_0] = poly3_make(v7, v2, v6);
  cube[RGT_1] = poly3_make(v2, v7, v3);
  cube[BOT_0] = poly3_make(v1, v6, v2);
  cube[BOT_1] = poly3_make(v6, v1, v5);
  cube[TOP_0] = poly3_make(v7, v4, v3);
  cube[TOP_1] = poly3_make(v4, v7, v8);

  for (i = 0; i < NTRI; i++)
    plist = poly_insert(plist, cube[i]);
    
  trilist_write(plist, stdout);

  exit(1);
}



