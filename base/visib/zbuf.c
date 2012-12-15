#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "geom.h"
#include "zbuf.h"

#define ZBUF(U,V) zbuf[U + V * zb_w]

static Real *zbuf = NULL;
static int zb_h = 0, zb_w = 0;


void zbuf_init(int w, int h)
{
  zbuf = (Real *) erealloc(zbuf, w * h * sizeof(Real));
  zb_w = w; zb_h = h;
  zbuf_clear(MAX_FLOAT);
}

void zbuf_clear(Real val)
{
  int x, y;

  for (y = 0; y < zb_h; y++)
    for (x = 0; x < zb_w; x++)
      ZBUF(x,y) = val;
}

int zbuf_store(Vector3 p)
{
  int x = p.x, y = p.y;

  if ((x > 0 && y > 0 && x < zb_w && y < zb_h) && p.z < ZBUF(x,y)) {
    ZBUF(x,y) = p.z;
    return TRUE;
  } else {
    return FALSE;
  }
}

Real zbuf_peek(Vector3 p)
{
  int x = p.x, y = p.y;
  return (x > 0 && y > 0 && x < zb_w && y < zb_h)? ZBUF(x,y) : MAX_FLOAT;
}
