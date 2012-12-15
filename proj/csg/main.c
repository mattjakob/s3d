#include <stdio.h>
#include "gp.h"
#include "csg.h"


main(int argc, char **argv)
{
  CsgNode *t;
  if((t = csg_parse()) == NULL)
    exit(-1);
  else
    csg_write(t, stdout);
  exit(0);
}
