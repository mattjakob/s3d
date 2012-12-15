
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include        "SDL.h"
#include "SDL_thread.h"

#include        "image.h"
#include        "gp.h"

void img_gpdisplay(Image *i);

int main(int argc, char *argv[])
{
  int quit = FALSE;
  float scale = 1.0;
  char *filein = "stdin";
  Image *i;

  if (argc == 2) {
    filein = argv[1];
  } else if (argc == 3) {
    filein = argv[1];
    scale = atof(argv[2]);
  }

  i = img_read(filein);
  gpopen(filein, i->w*scale, i->h*scale);
  gpwindow(0, i->w, 0, i->h);
  gpviewport(0., 1., 0., 1.);

  img_gpdisplay(i);
  gpswapbuffers();
  while (!quit) {
    Real x,y, wait=1;
    char* s=gpevent(wait,&x,&y);
    switch (s[0]) {
    case 'k':
      if (s[1]=='q') quit = TRUE;
      else if (s[1]=='d') img_gpdisplay(i);
      break;
    case 's':
      gpclear(0);
    case 'r':
      if (s[1] == '+') break;
      img_gpdisplay(i);
      break;
    default: break;
    }
  }
  gpclose(0);
  exit(0);
}

void img_gpdisplay(Image *i)
{
  int u, v, s;
  for (v = 0; v < i->h; v++) {
    for (u = 0; u < i->w; u++) {
      Color c = img_getc(i,u,v);
      gprgb(-1,(Real)RED(c)/255.,(Real)GRN(c)/255.,(Real)BLU(c)/255.);
      gpbox(u,u+1,v,v+1);
    }
  }
  gpflush();
}
