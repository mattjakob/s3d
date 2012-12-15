#include <stdlib.h>
#include "defs.h"

void *emalloc(int siz)
{
  void *buf, *malloc();

  if ((buf = malloc(siz)) == (char *)0)
    error("(emalloc) can't alloc space");
  return buf;
}

void *erealloc(void *buf, int siz)
{
  void *realloc();

  if ((buf = realloc(buf, siz)) == (char *)0)
    error("(erealloc) can't realloc space");
  return buf;
}

void efree(void *buf)
{
  if (buf) free(buf);
}
