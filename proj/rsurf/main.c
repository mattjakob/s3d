#include <stdio.h>
#include "poly.h"
#include "gener.h"

#define MAXPTS 2048
Vector3 g[MAXPTS];


int read_curve(void)
{
  int  k = 0;
  while (scanf("%lf %lf %lf\n" ,&(g[k].x),&(g[k].y),&(g[k].z)) != EOF)
    if (k++ > MAXPTS)
      break;
  return k;
}


main(int argc, char **argv)
{
  int k, n = 4;
  Poly *tl;

  if (argc == 2)
    n = atoi(argv[1]);
  k = read_curve();

  tl = rotsurf(k, g, n);
  trilist_write(tl, stdout);

  exit(0);
}
