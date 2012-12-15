#include "defs.h"

void error(char *message)
{
  fprintf(stderr, "fatal error: %s\n", message);
  exit(0);
}


void warning(char *message)
{
  fprintf(stderr, "warning: %s\n", message);
}
