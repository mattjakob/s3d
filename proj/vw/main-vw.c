#include        "image.h"
#include        "gp.h"
#include        "SDL.h"

void img_gpdisplay(Image *i);
void set_gpmap(CMap *m);
void set_gpgrey(void);
Image *img_uquant(Image *i);

main(argc, argv)
     int argc;
     char **argv;
{
  int quit = FALSE; Real ar;
  char *filein = "stdin";
  Image *i;

  if (argc == 2)
    filein = argv[1];

  i = img_read(filein);
  gpopen(filein, i->w, i->h);
  ar = gpwindow(0, i->w, 0, i->h);
  gpviewport(0., 1., 0., 1.);

  switch (img_type(i)) {
  case IMG_MONOCOL: 
    set_gpgrey(); break;
  case IMG_TRUECOL:
    i = img_quant_popul(i, 256, 4);
  case IMG_MAPPCOL:
    set_gpmap(i->m); break;
  default: break;
  }
  img_gpdisplay(i);
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
      gpcolor(img_geti(i,u,v));
      gpbox(u,u+1,v,v+1);
    }
  }
  gpflush();
}

void set_gpmap(CMap *m)
{
  int i, k;
  for (i=0; i<256; i++) {
    k=gprgb(i,(Real)(m->r[i])/255.,(Real)(m->g[i])/255.,(Real)(m->b[i])/255.);
    if (k==0 && i > 0)
      printf("color not bound %d (%d %d %d)\n",i,m->r[i],m->g[i],m->b[i]);
  }
}

void set_gpgrey(void)
{
  int i, k;
  for (i=0; i<256; i++) {
    k=gprgb(i,(Real)(i)/255.,(Real)(i)/255.,(Real)(i)/255.);
    if (k==0 && i > 0)
      printf("color not bound %d (%d %d %d)\n",i,i,i,i);
  }
}

Image *img_uquant(Image *i)
{
  int u,v;
  Image *q = img_init(IMG_MAPPCOL, i->w, i->h);

  for (v = 0; v < i->h; v++)
    for (u = 0 ; u < i->w; u++)
      img_puti(q, u, v, rgb_to_index(img_getc(i, u, v),3,3,2));
  return q;
}
