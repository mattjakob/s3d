
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "laux.h"
#include "geom.h"
#include "gp.h"
#include "mv.h"
#include "tk.h"

#include "SDL.h"


int but1()
{
  fprintf(stderr, "Button 1\n"); fflush(stderr);
  return 0;
}

int but2()
{
  fprintf(stderr, "Button 2\n"); fflush(stderr);
  return 1;
}

int main(int argc, char* argv[])
{
  Widget *w0;
  gpopen("tk test", 512, 512);
  tk_open(10);
  tk_widget(TK_BUTTON, .2, .5, but1, "Button 1");
  tk_widget(TK_BUTTON, .6, .5, but2, "Button 2");
  tk_mainloop();
  tk_close();
  gpclose(0);
}
